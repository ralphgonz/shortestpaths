
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Point {
    public:
    long x;
    long y;
};
inline bool operator==(const Point& lhs, const Point& rhs){ return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(const Point& lhs, const Point& rhs){return !(lhs == rhs);}

enum Direction {LEFT, RIGHT, UP, DOWN};
ostream &operator<<(ostream &os, Direction const &d) {
	switch (d) {
	case LEFT: os << "LEFT" ; break;
	case RIGHT: os << "RIGHT" ; break;
	case UP: os << "UP" ; break;
	case DOWN: os << "DOWN" ; break;
	}
    return os;
}

class Path {
   public:
    vector<Direction> steps;

    Path() {}
    Path(vector<Direction> _steps) : steps(_steps) {}
    Path(const Path& path) : steps(path.steps) {}
    void addStep(Direction direction);
};
void Path::addStep(Direction direction) {
    steps.push_back(direction);
}
ostream &operator<<(ostream &os, Path const &path) {
    for (vector<Direction>::const_iterator i=path.steps.begin() ; i != path.steps.end() ; ++i) {
        os << *i << ",";
    }
	os << endl;
    return os;
}

class Route {
public:
	Path path;
	Point position;
	Point end;

	Route(const Path& _path, const Point& _position, const Point& _end) : path(_path), position(_position), end(_end) {}
	void move(Direction direction);
	void printAllShortestPaths(ostream& os);
};
void Route::move(Direction direction) {
    path.addStep(direction);
    switch (direction) {
    case RIGHT: ++position.x; break;
    case LEFT: --position.x; break;
    case UP: ++position.y; break;
    case DOWN: --position.y; break;
    }
}
void Route::printAllShortestPaths(ostream &os) {
	if (position == end) {
		os << path;
	} else {
		// Recursively create new routes for each possible direction:
		if (position.x < end.x) {
			Route newRoute(*this);
			newRoute.move(RIGHT);
			newRoute.printAllShortestPaths(os);
		}
		if (position.x > end.x) {
			Route newRoute(*this);
			newRoute.move(LEFT);
			newRoute.printAllShortestPaths(os);
		}
		if (position.y < end.y) {
			Route newRoute(*this);
			newRoute.move(UP);
			newRoute.printAllShortestPaths(os);
		}
		if (position.y > end.y) {
			Route newRoute(*this);
			newRoute.move(DOWN);
			newRoute.printAllShortestPaths(os);
		}
	}
}

int main() {
    Point start;
    Point end;
    cin >> start.x;
    cin >> start.y;
    cin >> end.x;
    cin >> end.y;

    Route route(Path(), start, end);
    route.printAllShortestPaths(cout);
}
