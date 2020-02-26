#include "BehaviourTree.h"

/// <summary>
/// ******************************* Composite Definitions ********************************
/// </summary>

void BehaviourTree::Composite::addChild(DTNode* t_child)
{
	m_children.emplace_back(t_child);
}

void BehaviourTree::Composite::addChildren(std::initializer_list<DTNode*>&& t_newchildren)
{
	for (DTNode* child : t_newchildren)
	{
		addChild(child);
	}
}

template<typename CONTAINER>
inline void BehaviourTree::Composite::addchildren(const CONTAINER& t_newChildren)
{
	for (DTNode child :t_newChildren)
	{
		addChild(child);
	}
}


/// <summary>
/// ******************************* Selector Definitions ********************************
/// </summary>

bool BehaviourTree::Selector::run()
{
	for (DTNode* child : getChildren())
	{
		if (!child->run())
		{
			return true;
		}
		return false;
	}

}

/// <summary>
/// ******************************* Random Selector Definitions ********************************
/// </summary>

bool BehaviourTree::RandomSelector::run()
{
	for (DTNode* child : childrenShuffled())
	{
		if (!child->run())
		{
			return true;
		}
		return false;
	}
}


/// <summary>
/// ******************************* SEQUENCE Definitions ********************************
/// </summary>
bool BehaviourTree::Sequence::run()
{
	for (DTNode* child : getChildren())
	{
		if (!child->run())
		{
			return false;
		}
		return true;
	}
	return false;
}


/// <summary>
/// ******************************* Root Definitions ********************************
/// </summary>

bool BehaviourTree::Root::run()
{
	return getChild()->run(); 
}


/// <summary>
/// ******************************* Behaviour Tree Definitions ********************************
/// </summary>
void BehaviourTree::setRootChild(DTNode* t_rootChild) const
{
	m_root->setChild(t_rootChild);
}

bool BehaviourTree::run() const
{
	return m_root->run();
}


/// <summary>
/// ******************************* Action Definitions ********************************
/// </summary>
Action::Action(const std::string t_name, int prob) :
	m_name(t_name),
	ProbablilityOfSuccess(prob)
{

}

bool Action::run()
{
	if (std::rand() % 100 < ProbablilityOfSuccess)
	{
		std::cout << m_name << " Succeeded." << std::endl;
		return true;
	}
	std::cout << m_name << " Failed." << std::endl;
	return false;
}

/// <summary>
/// ******************************* Decorator Node Definitions ********************************
/// </summary>

void BehaviourTree::DecoratorNode::setChild(DTNode* t_child)
{
	m_child = t_child;
}

/// <summary>
/// ******************************* Inverter Definitions ********************************
/// </summary>
bool BehaviourTree::Inverter::run()
{

	return !getChild()->run();
}

/// <summary>
/// ******************************* Succeeder Definitions ********************************
/// </summary>
bool BehaviourTree::Succeeder::run()
{
	getChild()->run();
	return true;
}

/// <summary>
/// ******************************* Failer Definitions ********************************
/// </summary>
bool BehaviourTree::Failer::run()
{
	getChild()->run();
	return false;
}


/// <summary>
/// ******************************* Repeater Definitions ********************************
/// </summary>
bool BehaviourTree::Repeater::run()
{
	if (numRepeats == NOT_FOUND)
	{
		while (true)
		{
			getChild()->run();
		}
	}
	else
	{
		for (int i = 0; i < numRepeats -1; i++)
		{
			getChild()->run();
		}
		return getChild()->run();
	}
}

/// <summary>
/// ******************************* Repeat Until Fail Definitions ********************************
/// </summary>
bool BehaviourTree::RepeatUntilFail::run()
{
	while (getChild()->run()) {}

	return true;
}

/// <summary>
/// ******************************* Push To Stack Definitions ********************************
/// </summary>
template<typename T>
inline bool BehaviourTree::PushToStack<T>::run()
{
	this->stack.push(item);
	return true;
}


/// <summary>
/// ******************************* Get Stack Definitions ********************************
/// </summary>
template<typename T>
inline bool BehaviourTree::GetStack<T>::run()
{
	this->stack = m_obtainedStack;
	if (m_object)
	{
		this->stack.push(m_object);
	}
	return true;
}


/// <summary>
/// ******************************* Pop From Stack Definitions ********************************
/// </summary>
template<typename T>
inline bool BehaviourTree::PopFromStack<T>::run()
{
	if (this->stack.empty())
	{
		return false;
	}
	m_item = this->stack.top();
	this->stack.pop();
	return true;
}

/// <summary>
/// ******************************* Stack Is Empty Definitions ********************************
/// </summary>
template<typename T>
inline bool BehaviourTree::StackIsEmpty<T>::run()
{
	return this->stack.empty();
}

/// <summary>
/// ******************************* Set Variable Definitions ********************************
/// </summary>
template<typename T>
inline bool BehaviourTree::SetVariable<T>::run()
{
	m_variable = m_object;
	return true;
}

/// <summary>
/// ******************************* Is Null Definitions ********************************
/// </summary>
template<typename T>
inline bool BehaviourTree::IsNull<T>::run()
{
	return !m_object;
}

