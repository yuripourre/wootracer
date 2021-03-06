#include "stdafx.h"
#include "FuncCore.h"
#include "ParseUtils.h"
#include "FuncFactory.h"
#include "Functions.h"
#include "Vector3.h"
#include "Log.h"

DDistFunc::~DDistFunc()
{
	for (unsigned int i=0; i<mParam.size(); i++)
	{
		delete mParam[i];
	}
	mParam.clear();
}

DFuncParam::~DFuncParam()
{
	if (mVar) delete mVar;
}

void DProgram::Create(std::string& program)
{
	try
	{
		mStatements = DFuncFactory::Get().Create(program);
		mCompiled = true;
	}
	catch (int /*e*/)
	{
		LOG(Error, "Invalid Program");
		mStatements.clear();
		mCompiled = false;
	}
}

void DProgram::Run(DFunctionState& state) const
{
	for (unsigned int i=0; i<mStatements.size(); i++)
	{
		mStatements[i]->Evaluate(state);
	}
}

void DProgram::Reset()
{
	for (unsigned int i=0; i<mStatements.size(); i++)
	{
		delete mStatements[i];
	}
	mStatements.clear();
}

void DDistFunc::Read(std::string& arg)
{
/*	if (!ParseUtils::IsOpenBracket(arg))
		return;
//	if (mParam.size()==0) return;
	ParseUtils::StripOpenBracket(arg);
	for (int i=0; i<(int)mParam.size(); i++)
	{
		if (i!=0)
			ParseUtils::StripComma(arg);
		if (mParam[i]->mType == Vec)
			mParam[i]->mVar = (DVecFunc*)DFuncFactory::Get().CreateVec(arg);
		else if (mParam[i]->mType == Float)
			mParam[i]->mVar = (DFloatFunc*)DFuncFactory::Get().Create(arg);
		else if (mParam[i]->mType == RawFloat)
			mParam[i]->mVar = (DRawFloatFunc*)DFuncFactory::Get().CreateRawFloat(arg);
	}
	ParseUtils::StripCloseBracket(arg);
*/}

float DFuncParam::Evaluate(DFunctionState& state)
{
	DFloatFunc* var = (DFloatFunc*)mVar;

	if (var->mConstant)
	{
		if (!var->mSet)
		{
			var->mSet = true;
			mCacheFloat = var->Evaluate(state);
		}
		return mCacheFloat;
	}

	return var->Evaluate(state);
}
	
DVector3 DFuncParam::EvaluateVec(DFunctionState& state)
{
	DVecFunc* var = (DVecFunc*)mVar;

	if (var->mConstant)
	{
		if (!var->mSet)
		{
			var->mSet = true;
			mCacheVector3= var->Evaluate(state);
		}
		return mCacheVector3;
	}

	return var->Evaluate(state);
}

void DFuncParam::EvaluateNull(DFunctionState& state)
{
	((DNullFunc*)mVar)->Evaluate(state);
}
