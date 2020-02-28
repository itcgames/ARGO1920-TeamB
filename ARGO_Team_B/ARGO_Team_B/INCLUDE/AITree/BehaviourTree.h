#ifndef BEHAVIOURTREE_H
#define BEHAVIOURTREE_H



#include "Enums.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <initializer_list>
#include <stack>
#include <list>
#include <iostream>
#include <algorithm>
#include <sstream>


/// <summary>
/// *********************************** BEHAVIOUR TREE CLASS ***********************************************
/// </summary>
class BehaviourTree
{
public:
	/// <summary>
	/// *********************************** NODE CLASS ***********************************************
	/// </summary>
	class DTNode
	{
	public:
		virtual bool run() = 0;
	};

	/// <summary>
	/// *********************************** COMPOSITE CLASS ***********************************************
	/// </summary>
	class Composite : public DTNode
	{
	private:
		std::vector<DTNode* > m_children;

	public:
		const std::vector<DTNode* >& getChildren() const { return m_children; };
		void addChild(DTNode* t_child);
		void addChildren(std::initializer_list<DTNode*>&& t_newchildren);
		template <typename CONTAINER>
		void addchildren(const CONTAINER& t_newChildren);

	protected:
		std::vector<DTNode*> childrenShuffled() const
		{
			std::vector<DTNode* > temp = m_children;
			std::random_shuffle(temp.begin(), temp.end());
			return temp;
		};

	};

	/// <summary>
	/// *********************************** SELECTOR CLASS ***********************************************
	/// </summary>
	class Selector : public Composite
	{
	public:
		virtual bool run() override;
	};

	/// <summary>
	/// *********************************** RANDOM SELECTOR CLASS ***********************************************
	/// </summary>
	class RandomSelector : public Composite {
	public:
		virtual bool run() override;
	};

	/// <summary>
	/// *********************************** SEQUENCE CLASS ***********************************************
	/// </summary>
	class Sequence : public Composite
	{
	public:
		virtual bool run() override;

	protected:
	};

	/// <summary>
	/// *********************************** Decorator Node CLASS ***********************************************
	/// </summary>
	class DecoratorNode : public DTNode
	{
	private:
		DTNode* m_child;
	protected:
		DTNode* getChild() const { return m_child; };
	public:
		void setChild(DTNode* t_child);
	};


	/// <summary>
	/// *********************************** Inverter CLASS ***********************************************
	/// </summary>
	class Inverter : public DecoratorNode
	{
	private:
		virtual bool run() override;
	};

	/// <summary>
	/// *********************************** Succeeder CLASS ***********************************************
	/// </summary>
	class Succeeder: public DecoratorNode
	{
	private:
		virtual bool run() override;
	};

	/// <summary>
	/// *********************************** Failer CLASS ***********************************************
	/// </summary>
	class Failer : public DecoratorNode
	{
	private:
		virtual bool run() override;
	};

	/// <summary>
	/// *********************************** Repeater CLASS ***********************************************
	/// </summary>
	class Repeater : public DecoratorNode
	{
	private:
		int numRepeats;
		static const int NOT_FOUND = -1;
		Repeater(int t_num = NOT_FOUND) : numRepeats(t_num) {};
		virtual bool run() override;
	};

	/// <summary>
/// *********************************** Repeat Until Fail CLASS ***********************************************
/// </summary>
	class RepeatUntilFail : public DecoratorNode
	{
	private:
		virtual bool run() override;
	};



	/// <summary>
	/// *********************************** StackNode CLASS ***********************************************
	/// </summary>
	template<typename T>
	class StackNode : public DTNode
	{
	protected:
		std::stack<T*>& stack;
		StackNode(std::stack<T*>& s) : stack(s) {};
		virtual bool run() = 0;
	};

	/// <summary>
	/// *********************************** Push To Stack CLASS ***********************************************
	/// </summary>
	template<typename T>
	class PushToStack : public StackNode<T>
	{
	private: T*& item;

	public: PushToStack(T*& t, std::stack<T*>& s) : StackNode<T>(s), item(t) {}

	private:
		virtual bool run() override;
	};

	/// <summary>
	/// *********************************** Get Stack CLASS ***********************************************
	/// </summary>
	template<typename T>
	class GetStack : public StackNode<T>
	{
	private: 
		const std::stack<T*>& m_obtainedStack;
		T*& m_object;

	public: 
		GetStack(std::stack<T*>& s, const std::stack<T*>& t_o, T* t = nullptr) : StackNode<T>(s), m_obtainedStack(t_o), m_object(t) {};

	private:
		virtual bool run() override;
	};

	/// <summary>
	/// *********************************** Pop From Stack CLASS ***********************************************
	/// </summary>
	template<typename T>
	class PopFromStack : public StackNode<T>
	{
	private:
		T*& m_item;

	public: 
		PopFromStack(T*& t, std::stack<T*>& s) : StackNode<T>(s), m_item(t) {};

	private:
		virtual bool run() override;
	};

	/// <summary>
	/// ***********************************  Stack Is Empty CLASS ***********************************************
	/// </summary>
	template<typename T>
	class StackIsEmpty : public StackNode<T>
	{
	public:
		StackIsEmpty(std::stack<T*>& s) : StackNode<T>(s) {};

	private:
		virtual bool run() override;
	};

	/// <summary>
	/// ***********************************  Set Variable CLASS ***********************************************
	/// </summary>
	template<typename T>
	class SetVariable : public BehaviourTree::DTNode
	{
	private:
		T*& m_variable, *& m_object;
	public:
		SetVariable(T*& t, T& obj) : m_variable(t), m_object(obj) {};
		virtual bool run() override;
	};


	/// <summary>
	/// ***********************************  Is Null CLASS ***********************************************
	/// </summary>
	template<typename T>
	class IsNull : public BehaviourTree::DTNode
	{
	private:
		T*& m_object;
	public:
		IsNull(T*& t) : m_object(t) {};
		virtual bool run() override;
	};

	/// <summary>
	/// *********************************** ROOT CLASS ***********************************************
	/// </summary>
	class Root : public DecoratorNode
	{
	private:
		friend class BehaviourTree;
		virtual bool run() override;
	};
private:
	Root* m_root;

public:
	BehaviourTree() : m_root(new Root) {};
	void setRootChild(DTNode* t_rootChild) const;
	bool run() const;
};

/// <summary>
/// *********************************** Action CLASS ***********************************************
/// </summary>
class Action : public BehaviourTree::DTNode
{
private:
	std::string m_name;
	int ProbablilityOfSuccess;

public:
	Action(const std::string t_name, int prob);
private:
	virtual bool run() override;
};

#endif
