#pragma once

class StrategyBase
{
public:
	virtual float update(float ratio) = 0;
};

class LinearInStrategy : public StrategyBase
{
public:
	virtual float update(float ratio)
	{
		return 1;
	}
};

class exponentialInStrategy : public StrategyBase
{
public:
	virtual float update(float ratio)
	{
		return ratio;
	}
};
class sinInStrategy : public StrategyBase
{
public:
	virtual float update(float ratio)
	{
		return sinf(ratio * 2 * 3.14);
	}
};