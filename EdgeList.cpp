/* /////////////////////////////////////////////////////////////////////////////

This is the Data Structure Doubly-Connected Edge list, which is used to
store map information and do some common operations on the map.

This structure maintains three list of records: The list of vertices, list of
half-edges, and the list of faces.

Each edge is incident to two faces, yet we can see the egdge as two half-edges
then edge half-edge is incident to one face. The two half-edges induced by one
edge are called twins. The orientations of twin edges are opposite, and such
that if you go through a list of half-edges surrounding one face, that face
always lies on the left.

Here is the details of the data structure:

1. Vertex
	
	Each vertex records its x and y coordinates. It also stores ONE pointer to
	an arbitrary half-edge that has this vertex as origin.

2. Face
	
	Each vertex records ONE pointer to an arbitrary half-edge in its outer
	boundary. For the unbounded face this pointer is nil. It also stores a list
	of pointers, each pointing to a half-edge of one possibly existing hole.

	Additionally, the face records some other information called its attributes.
	This is useful if this structure represents some map and the face may
	represent countries or different types of fields, etc.

3. Half-Edge

	Each Half-Edge records a vertex pointer to its origin, a half-edge pointer
	to its twin, and a face pointer to the face it surrounds. Then it stores
	two half-edge pointers to the next half-edge and the previous half-edge
	surrounding the same face.

	Note: The half-edge does not store the vertex pointer to the destination.
	Since e.twin().origin() simply returns the destination.

///////////////////////////////////////////////////////////////////////////// */

#include <cstdlib>
#include <list>

// Pre-declaration of class HalfEdge, for use in class Vertex and class Face
class HalfEdge;
class Vertex
{
public:
	Vertex(double x, double y)
	:_x(x), _y(y), _e(NULL)
	{}

	inline double x() const {return _x;}
	inline double y() const {return _y;}
	inline HalfEdge *e() const {return _e;}
private:
	double _x;
	double _y;
	HalfEdge *_e;
};

class Face
{
public:
	Face():_outer(NULL){}

	// Construct face from an array of existing vertices
	void fromVertices(Vertex *v[], int n);

	inline HalfEdge* outerEdge() const {return _outer;}
	inline std::list<HalfEdge*> & innerEdges() {return _inners;}
private:
	HalfEdge* _outer;
	std::list<HalfEdge*> _inners;
};

class HalfEdge
{
public:
	HalfEdge(){}

	inline Vertex* origin() const {return _origin;}
	inline HalfEdge* twin() const {return _twin;}
private:
	Vertex *_origin;
	HalfEdge *_twin;
};

class DCEdgeList
{
public:
	DCEdgeList(){}
private:
};

// Construct face from an array of existing vertices
void Face::fromVertices(Vertex *v[], int n)
{
}
