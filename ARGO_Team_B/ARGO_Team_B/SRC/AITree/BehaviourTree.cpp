#include "BehaviourTree.h"

/// <summary>
/// *********************************** BEHAVIOUR DEFINITIONS ***********************************************
/// </summary>
DTBehaviour::DTBehaviour()
{
}

DTBehaviour::DTBehaviour(DTNode& t_node)
{
}

DTBehaviour::~DTBehaviour()
{
}

void DTBehaviour::setup(DTNode& t_node)
{
	teardown();

	m_node = &t_node;
	m_task = t_node.create();
}

void DTBehaviour::teardown()
{
	if (m_task == nullptr)
	{
		return;
	}

	assert(m_status != NodeStatus::BH_RUNNING);
	m_node->destroy(m_task);
	m_task = NULL;
}

NodeStatus DTBehaviour::tick()
{
	if (m_status == NodeStatus::BH_INVALID)
	{
		m_task->onInitialise();
	}

	m_status = m_task->update();


	if (m_status == NodeStatus::BH_RUNNING)
	{
		m_task->onTerminate(m_status);
	}

	return m_status;
}

DTTask* DTBehaviour::getTask() const
{
	return dynamic_cast<DTTask*>(m_task);
}


/// <summary>
/// *********************************** MOCK TASK DEFINITIIONS ***********************************************
/// </summary>
MockTask::MockTask(DTNode& t_node) :
	DTTask(t_node),
	m_initialiseCalled(0),
	m_terminateCalled(0),
	m_updateCalled(0),
	m_returnStatus(NodeStatus::BH_RUNNING),
	m_terminateStatus(NodeStatus::BH_INVALID)
{
}

void MockTask::onInitialise()
{
	m_initialiseCalled++;
}

void MockTask::onTerminate(NodeStatus t_s)
{
	m_terminateCalled++;
	m_terminateStatus = t_s;
}

NodeStatus MockTask::update()
{
	++m_updateCalled;
	return m_returnStatus;
}


/// <summary>
/// *********************************** MOCK NODE DEFINITIONS ***********************************************
/// </summary>
void MockNode::destroy(DTTask*)
{
}

DTTask* MockNode::create()
{
	m_task = new MockTask(*this);
	return m_task;
}

MockNode::~MockNode()
{
	delete m_task;
}

MockNode::MockNode() :
	m_task(nullptr)
{
}



/// <summary>
/// *********************************** SEQUENCE DEFINITIONS ***********************************************
/// </summary>
Sequence::Sequence(Composite& t_node)
	: DTTask(t_node)
{
}

Composite& Sequence::getNode()
{
	return *static_cast<Composite*>(m_node);
	// TODO: insert return statement here
}

void Sequence::onInitialise()
{
	m_currentChild = getNode().m_childrenNodes.begin();
	m_currentBehaviour.setup(**m_currentChild);
}

NodeStatus Sequence::update()
{
	for (; ;)
	{
		NodeStatus s = m_currentBehaviour.tick();
		if (s != NodeStatus::BH_SUCCESS)
		{
			return s;
		}
		if (++m_currentChild == getNode().m_childrenNodes.end())
		{
			return NodeStatus::BH_SUCCESS;
		}
		m_currentBehaviour.setup(**m_currentChild);
	}
}


/// <summary>
/// *********************************** MOCK COMPOSITE DEFINITIONS ***********************************************
/// </summary>
MockComposite::MockComposite(size_t t_size)
{
	for (size_t i = 0; i < t_size; ++i)
	{
		m_childrenNodes.push_back(new MockNode);
	}

}
MockComposite::~MockComposite()
{
	for (size_t i = 0; i < m_childrenNodes.size(); ++i)
	{
		delete(m_childrenNodes[i]);
	}
}

MockTask& MockComposite::operator[](size_t t_index)
{
	ASSERT(t_index < m_childrenNodes.size());
	MockTask* task = static_cast<MockNode*>(m_childrenNodes[t_index])->m_task;
	ASSERT(task != NULL);
	return *task;
	
}

DTTask* MockComposite::create()
{
	return new MockTask(*this);
}

void MockComposite::destroy(DTTask* t_task)
{
	delete(t_task);
}



/// <summary>
/// *********************************** SELECTOR DEFINITIONS ***********************************************
/// </summary>

Selector::Selector(Composite& t_node):
	DTTask(t_node)
{
}

Composite& Selector::getNode()
{
	return *static_cast<Composite*>(m_node);
}

void Selector::onInitialise()
{
	m_currentChild = getNode().m_childrenNodes.begin();
	m_behaviour.setup(**m_currentChild);
}

NodeStatus Selector::update()
{
	for (;;)
	{
		NodeStatus s = m_behaviour.tick();

		if (s != NodeStatus::BH_FAILURE)
		{
			return s;
		}
		if (++m_currentChild == getNode().m_childrenNodes.end())
		{
			return NodeStatus::BH_FAILURE;
		}
		m_behaviour.setup(**m_currentChild);
	}
}	
