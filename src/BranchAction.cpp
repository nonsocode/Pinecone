#include "../h/BranchAction.h"
#include "../h/ErrorHandler.h"

BranchAction::BranchAction(ActionPtr leftInputIn, ActionPtr actionIn, ActionPtr rightInputIn)
		:Action(actionIn->getReturnType(), Void, Void, "BRANCH")
{
	action=actionIn;
	leftInput=leftInputIn;
	rightInput=rightInputIn;
	
	if (leftInput->getInLeftType()!=Void || leftInput->getInRightType()!=Void)
	{
		error.log(leftInput->getDescription() + " put into branch even though its inputs are not void", INTERNAL_ERROR);
	}
	
	if (rightInput->getInLeftType()!=Void || rightInput->getInRightType()!=Void)
	{
		error.log(rightInput->getDescription() + " put into branch even though its inputs are not void", INTERNAL_ERROR);
	}
	
	if (leftInput->getReturnType()!=action->getInLeftType())
	{
		error.log(leftInput->getDescription() + " return type is not the same as the left input of " + action->getDescription(), INTERNAL_ERROR);
	}
	
	if (rightInput->getReturnType()!=action->getInRightType())
	{
		error.log(rightInput->getDescription() + " return type is not the same as the right input of " + action->getDescription(), INTERNAL_ERROR);
	}
}

string BranchAction::getDescription()
{
	if (leftInput && action && rightInput)
		//return getReturnType().toString() + " <- [" + leftInput->getDescription() + "].[" + action->getDescription() + "]:[" + rightInput->getDescription() + "]";
		return getReturnType()->getName() + " <- " + leftInput->getDescription() + "." + action->getDescription() + ":" + rightInput->getDescription();
	else
		return "[branch with null element]";
}

void* BranchAction::execute(void* inLeft, void* inRight)
{
	
	void* leftData=leftInput->execute(nullptr, nullptr);
	void* rightData=rightInput->execute(nullptr, nullptr);
	void* outData=action->execute(leftData, rightData);
	leftInput->getReturnType()->deleteVoidPtr(leftData);
	rightInput->getReturnType()->deleteVoidPtr(rightData);
	return outData;
}


