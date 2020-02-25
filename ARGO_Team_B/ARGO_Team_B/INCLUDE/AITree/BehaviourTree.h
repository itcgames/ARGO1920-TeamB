#ifndef BEHAVIOURTREE_H
#define BEHAVIOURTREE_H

#endif // !BEHAVIOURTREE


#include "Enums.h"
#include <vector>
#include "Shared.h"

class DTNode;
class DTTask;

typedef std::vector<DTNode*> Nodes;

/// <summary>
/// *********************************** BEHAVIOUR TREE CLASS ***********************************************
/// </summary>
class BehaviourTree
{
};

/// <summary>
/// *********************************** NODE CLASS ***********************************************
/// </summary>
class DTNode
{
public:
	virtual DTTask* create() = 0;
	virtual void destroy(DTTask*) = 0;

	virtual ~DTNode() {};
};

/// <summary>
/// *********************************** TASK CLASS ***********************************************
/// </summary>
class DTTask
{
public:
	DTTask(DTNode& t_node) :
		m_node(&t_node) {};

	virtual ~DTTask() {};

	virtual NodeStatus update() = 0;

	virtual void onInitialise() {};
	virtual void onTerminate(NodeStatus t_status) {};

protected:
	DTNode* m_node;

};



/// <summary>
/// *********************************** BEHAVIOUR CLASS ***********************************************
/// </summary>
class DTBehaviour
{
protected:
	DTTask* m_task;
	DTNode* m_node;
	NodeStatus m_status;

public:
	DTBehaviour();

	DTBehaviour(DTNode& t_node);

	~DTBehaviour();

	void setup(DTNode& t_node);
	void teardown();

	NodeStatus tick();

	DTTask* getTask() const;
};


/// <summary>
/// *********************************** MOCK TASK CLASS ***********************************************
/// </summary>
struct MockTask : public DTTask
{
	int m_initialiseCalled;
	int m_terminateCalled;
	int m_updateCalled;

	NodeStatus m_returnStatus;
	NodeStatus m_terminateStatus;


	MockTask(DTNode& t_node);


	virtual NodeStatus update();
	virtual void onInitialise();
	virtual  void onTerminate(NodeStatus t_s);
	
};


/// <summary>
/// *********************************** MOCK NODE CLASS ***********************************************
/// </summary>
struct MockNode : public DTNode
{
public:
	virtual void destroy(DTTask*);
	virtual DTTask* create();

	virtual ~MockNode();

	MockNode();

	MockTask* m_task;

};

/// <summary>
/// *********************************** COMPOSITE CLASS ***********************************************
/// </summary>
class Composite : public DTNode
{
public:
	Nodes m_childrenNodes;
};



/// <summary>
/// *********************************** SEQUENCE CLASS ***********************************************
/// </summary>
class Sequence : public DTTask
{
public:
	Sequence(Composite& t_node);

	Composite& getNode();

	virtual void onInitialise();

	virtual NodeStatus update();

protected:

	DTBehaviour m_currentBehaviour;
	Nodes::iterator m_currentChild;

};

/// /// <summary>
/// *********************************** MOCK COMPOSITE CLASS ***********************************************
/// </summary>
class MockComposite : public Composite
{
public:
	MockComposite(size_t t_size);
	~MockComposite();

	MockTask& operator [](size_t t_index);

	virtual DTTask* create();
	virtual void destroy(DTTask* t_task);

};


/// /// <summary>
/// *********************************** SELECTOR CLASS ***********************************************
/// </summary>
class Selector : public DTTask
{
public:
	Selector(Composite& t_node);
	Composite& getNode();

	virtual void onInitialise();


	virtual NodeStatus update();

protected:
	Nodes::iterator m_currentChild;
	DTBehaviour m_behaviour;
};
