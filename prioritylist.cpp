#include "priorityList.h"
#include "city.h"
#include "vertex.h"
PriorityList::PriorityList() :first{ nullptr }
{

}


 void PriorityList::push(Vertex* element)
{
	nodeQueue* newNode = new nodeQueue{ element };
	if (first == nullptr)
	{
		first = newNode;
		newNode->next = nullptr;
		size++;
	}
	else {
		nodeQueue* temp = first;
		nodeQueue* prev = nullptr;
		while (temp != nullptr)
		{
			if (temp->current->getDistance() > newNode->current->getDistance())
			{
				newNode->next = temp;
				if (prev == nullptr)
				{
					first = newNode;
				}
				else {
					prev = newNode;
				}
				return;
			}
			prev = temp;
			if(temp->next !=nullptr)
				temp = temp->next;
			else {
				temp->next = newNode;
				break;
			}
		}
		
		
	}
}


 void PriorityList::showList()
{
	nodeQueue* temp = first;
	while (temp != nullptr)
	{
		std::cout << " " << temp->current->getCity()->getName() << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
}


 int PriorityList::getSize()
 {
	 return this->size;
 }


 bool PriorityList::isEmpty()
 {
	 if (first == nullptr)
		 return true;
	 else
		 return false;
 }

 Vertex* PriorityList::front()
 {
	 return first->getNode();
 }

 void PriorityList::pop()
 {
	 if (first->next != nullptr)
	 {
		 nodeQueue* temp = first;
		 first = first->next;
		 delete temp;
	 }
	 else {
		 delete first;
		 first = nullptr;
	 }
 }

