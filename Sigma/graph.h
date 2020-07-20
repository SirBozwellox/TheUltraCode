#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

extern int stateSize;

class state {
	public:
		char name[20];
		float x;
		float y;
		bool active = FALSE;
		bool lit = FALSE;
		state();
		state(char inName[20], float inx, float iny);
		void draw(bool enabled);
		void drawBack(bool enabled);
		void drawShadow();
		void drawGlow();
		bool mouseOver();
		float getMouseDist();
		float getMouseAngle();
		float rot0 = pi * 1.5;
		float rot1 = pi * 0.5;
		bool final = FALSE;
};

class edge {
	public:
		char type;
		int fromState = -1;
		int toState = -1;
		edge();
		edge(char inType, int inFromState, int inToState);
};

class graph {
public:
	state stateList[100];
	edge edgeList[100];
	int currentState = -1;
	int lastState = -1;
	graph();
	void draw();
	void addState(state newState);
	void addEdge(edge newEdge);
	void removeState(int i);
	void removeEdge(int i);
	bool edgeExists(char inType, int inFromState);
	bool edgeExists(char inType, int inFromState, int inToState);
	bool edgeExists(int inFromState, int inToState);
	int findEdge(char inType, int inFromState);
	char getNextLetter();
	void drawEdge(int fromState, int toState, char type);
	void drawEdgeReal(int fromState, int toState, char type);
	void drawStartingEdge(bool active);
	void drawEdgeShadow(int fromState, int toState, char type);
	void drawEdgeGlow(int fromState, int toState, char type, float distance);
	void drawEdgeSpark(int fromState, int toState, int type);
	void drawBulbGlow();
	int getStateNum();
};

#endif
