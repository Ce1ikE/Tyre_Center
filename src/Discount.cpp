#include "../headers/Discount.h"

Discount::Discount()
{

};

void Discount::setVAT(int newVAT)
{
	VAT = newVAT;
};

int Discount::getVAT()
{
	return VAT;
};

void Discount::setDiscountCorpCust(int newDiscountCorpCust)
{
	discountCorpCust = newDiscountCorpCust;
};

int Discount::getDiscountCorpCust()
{
	return discountPrivCust;
};

void Discount::setDiscountPrivCust(int newDiscountPrivCust)
{
	discountPrivCust = newDiscountPrivCust;
};

int Discount::getDiscountPrivCust()
{
	return discountPrivCust;
};

void Discount::setDiscountExPrivCust(int newDiscountExPrivCust)
{
	discountExPrivCust = newDiscountExPrivCust;
};

int Discount::getDiscountExPrivCust()
{
	return discountExPrivCust;
};

void Discount::setAmountDiscountRequirement_Corp(int newRequirement)
{
	ammountSetsRequirement_Corp = newRequirement;
};

int Discount::getAmountDiscountRequirement_Corp(void)
{
	return ammountSetsRequirement_Corp;
};

void Discount::setAmountDiscountRequirement_Priv(int newRequirement)
{
	ammountSetsRequirement_Priv = newRequirement;
};

int Discount::getAmountDiscountRequirement_Priv(void)
{
	return ammountSetsRequirement_Priv;
};

void Discount::setMatchingDiscountRequirement_Priv(int newRequirement)
{
	matchingSetsRequirement = newRequirement;
};

int Discount::getMatchingDiscountRequirement_Priv(void)
{
	return matchingSetsRequirement;
};

void Discount::setMinWidthTyre(int newMinWidthTyre)
{
	if (newMinWidthTyre < 0)
	{
		min_W_t = 155;
	}
	else
	{
		min_W_t = newMinWidthTyre;
	}
};

int Discount::getMinWidthTyre(void)
{
	return min_W_t;
};

void Discount::setMaxWidthTyre(int newMaxWidthTyre)
{
	if (newMaxWidthTyre <= min_W_t)
	{
		max_W_t = min_W_t + (int)S_t * 3;
		return;
	}

	if (newMaxWidthTyre <= 0)
	{
		max_W_t = 185;
	}
	else
	{
		max_W_t = newMaxWidthTyre;
	}
};

int Discount::getMaxWidthTyre(void)
{
	return max_W_t;
};

void Discount::setMinWidthRim(int newMinWidthRim)
{
	if (newMinWidthRim <= 0)
	{
		min_W_r = 5;
	}
	else
	{
		min_W_r = newMinWidthRim;
	}
};

int Discount::getMinWidthRim(void)
{
	return min_W_r;
};

void Discount::setIncrementationStepTyre(float incrementationStep)
{
	S_t = incrementationStep;
};

float Discount::getIncrementationStepTyre(void)
{
	return S_t;
};

void Discount::setIncrementationStepRim(float incrementationStep)
{
	S_r = incrementationStep;
};

float Discount::getIncrementationStepRim(void)
{
	return S_r;
};

void Discount::setMaxTiers(int newMaxTiers)
{
	if (newMaxTiers <= 0)
	{
		maxTiers = 16;
	}
	else
	{
		maxTiers = newMaxTiers;
	}
};

int Discount::getMaxTiers(void)
{
	return maxTiers;
};

bool Discount::calculateMatch(int diamter_r, int diamter_t, int width_r, int width_t)
{
	if (diamter_r != diamter_t)
	{
		return false;
	}

	int X_l{ static_cast<int>(std::floor((width_t - min_W_t) / S_t) + 1) };

	int X_u{ static_cast<int>(std::floor((min_W_t - max_W_t) / S_t) + X_l) };

	float Y{ ((width_r - min_W_r) / S_r) + 1 };

	if (X_l <= Y && Y <= X_u )
	{
		return true;
	}
	else
	{
		return false;
	}
};

void Discount::displayDiscountTable(void)
{
	std::cout
		<< std::left
		<< TXT_COLOR(109)
		<< std::setw(40) << "\nVAT" << " | " << VAT
		<< std::setw(40) << "\nDiscount corporate customers" << " | " << discountCorpCust
		<< std::setw(40) << "\nDiscount private customers" << " | " << discountPrivCust
		<< std::setw(40) << "\nExtra Discount private customers" << " | " << discountExPrivCust
		<< std::endl
		<< RESET_COLOR;
};

void Discount::displayMatch_Tyre_Rim(void)
{
	std::cout
		<< TXT_COLOR(41)
		<< std::right
		<< std::setw(10) << "Tier |"
		<< std::setw(15) << "Width Rim |"
		<< std::setw(20) << "min Width Tyre |"
		<< std::setw(20) << "best Width Tyre |"
		<< std::setw(20) << "max Width Tyre |\n";
	line(120, '-');
	for (int i = 0; i < maxTiers; i++)
	{
		std::cout
			<< std::setw(10) << (i + 1)
			<< std::setw(15) << (float)(min_W_r + i * S_r)
			<< std::setw(20) << (float)(min_W_t + i * S_t)
			<< std::setw(7) << (float)((min_W_t + i * S_t) + 10)
			<< std::setw(5) << " or "
			<< std::setw(8) << (float)((max_W_t + i * S_t) - 10)
			<< std::setw(20) << (float)(max_W_t + i * S_t)
			<< "\n";
	}
	line(120, '-');
	std::cout << std::endl << RESET_COLOR;

};


