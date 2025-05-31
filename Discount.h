#pragma once
#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include "TyreCenterHeader.h"

class Discount
{
public:
	Discount();

	void setVAT(int);
	int getVAT(void);
	void setDiscountCorpCust(int);
	int getDiscountCorpCust(void);
	void setDiscountPrivCust(int);
	int getDiscountPrivCust(void);
	void setDiscountExPrivCust(int);
	int getDiscountExPrivCust(void);
	void setAmountDiscountRequirement_Corp(int);
	int getAmountDiscountRequirement_Corp(void);
	void setAmountDiscountRequirement_Priv(int);
	int getAmountDiscountRequirement_Priv(void);
	void setMatchingDiscountRequirement_Priv(int);
	int getMatchingDiscountRequirement_Priv(void);
	void setMinWidthTyre(int);
	int getMinWidthTyre(void);
	void setMaxWidthTyre(int);
	int getMaxWidthTyre(void);
	void setMinWidthRim(int);
	int getMinWidthRim(void);
	void setIncrementationStepTyre(float);
	float getIncrementationStepTyre(void);
	void setIncrementationStepRim(float);
	float getIncrementationStepRim(void);
	void setMaxTiers(int);
	int getMaxTiers(void);

	bool calculateMatch(int,int,int,int);
	void displayDiscountTable(void);
	void displayMatch_Tyre_Rim(void);

private:
	// Discount and taxes applied to a customer of type "Corp" (corporate)
	// VAT == Value Added Tax
	int VAT{ 21 };
	int discountCorpCust{ 20 };

	// Discount and taxes applied to a customer of type "Priv" (private)
	int discountPrivCust{ 10 };
	int discountExPrivCust{ 5 };

	// Discount condition variable which decide when a discount is applied for the corporate customer
	int ammountSetsRequirement_Corp{ 10 };

	// Discount condition variables which decide when a discount is applied for the private customer
	int ammountSetsRequirement_Priv{ 1 };
	int matchingSetsRequirement{ 1 };

	// variables used to calculate if a rim matches a tyre set
	int min_W_t{ 155 };
	int max_W_t{ 185 };
	int min_W_r{ 5 };

	float S_t{ 10 };
	float S_r{ 0.5 };

	int maxTiers{ 16 };
};
#endif // DISCOUNT_H!

// Rims are sold by sets of (4)
// Tyres are sold by piece (1) or by sets of (2) or (4)
// -----------------------------------------------------------------------------
// Discount for the "Corp" customer is applied if :
// 
// in "Invoice" : (x*Rims(4) + y*Tyres(2) + z*Tyres(4)) && x + y + z >= 10 
// -----------------------------------------------------------------------------
// Discount for the "Priv" customer is applied if : 
// 
// in "Invoice" : (x*Tyres(4)) && x >= 1
// -----------------------------------------------------------------------------
// Extra discount for the "Priv" customer is applied if : 
// 
// in "Invoice" : (x*Tyres(4).getWidth()  == y*Rims(4).getWidth()) && x*Tyres(4).getDiameter() == y*Rims(4).getDiameter()  && x >= 1 && y >= 1
// -----------------------------------------------------------------------------

// 
/*
	following calculations are based on this table:
	=> https://www.audi-a2.nl/uploads/imageupload/843/I11NUHVH8MPV.JPG
	!! we do not sell lower then this !!
	------------------------------------
	min_W_t = minimum width (tier 1) tyre = 155  (mm)
	max_W_t = maximum width (tier 1) tyre = 185  (mm)
	min_W_r = minimum width (tier 1) rim  = 5.0  (inch)

	W_t = tyre.getWidth()
	W_r = rim.getWidth()

	S_t = incrementation step for tyres (from tier to tier) = 10 (mm)
	S_r = incrementation step for rim (from tier to tier)   = 0.5 (inch)

	X_l = number of steps for lowerbound tyre
	X_u = number of steps for upperbound tyre
	Y = number of steps for rim

	X_l can be calculted by reducing W_t with the min_W_t and dividing by S_t and then rounded down
	Y can also be calculated similary but we do not round down
	X_u can be calculated by reducing the min_W_t - max_W_t and afterwards dividing by S_t and finally add the X_l
	in such a way that we have a range 

	X_l = std::floor((W_t - min_W_t) / S_t) + 1
	X_u = std::floor(((min_W_t - max_W_t) / S_t) + X_l)

	Y = ((W_r - min_W_r) / S_r) + 1

	the reason i do +1 both to X_l and Y is because i have no tier 0 and only start at 1 (nothing special)
	there can be overlapping between the tiers of the tyres
	but that is not important
	=> https://lh4.googleusercontent.com/proxy/e12wvchrpV-JfYTtNtDLL_QzyonH-BdVGE1muMSZzI6NdWRb_MuLKdaTGiwE54ht63Bbkp_oBIouPtYyo-P7ZbjqCLlYgND6pGFzFn3Nw6nBKOmv_m3hoH7tfBnuD58-QWlw37RegJE4vGQKG8EOFJwylEw

	example:
	--------
	min_W_t = 155
	max_W_t = 185
	min_W_r = 5.0

	W_t = 172
	W_r = 6.6

	S_t = 10
	S_r = 0.5

	X_l = std::floor((172 - 155 )/ 10) + 1 = std::floor(1.7) + 1 = 2
	X_u = std::floor((X_l + ((155 - 185)/ 10)) = 5

	Y = (6.6 - 5.0 )/ 0.5 = 3.2

	<=> X_l <= Y   <= X_u
	<=> 2   <= 3.2 <= 5 
	<=> True

+--------+-------------------+---------------------------+----------------------------+----------------------------+
| Tier   | Breedte van de    | Minimum breedte           | Ideale breedte             | Maximale breedte           |
|	     | velg (Width of    | van de band (Minimum      | van de band (Ideal Width   | van de band (Maximum       |
|	     | the rim)          | Tire Width)               | of the Tire)               | Tire Width)                |
+--------+-------------------+---------------------------+----------------------------+----------------------------+
|	1    | 5,0 Inch          | 155 mm                    | 165 of 175 mm              | 185 mm                     |
|	2    | 5,5 Inch          | 165 mm                    | 175 of 185 mm              | 195 mm                     |
|	3    | 6,0 Inch          | 175 mm                    | 185 of 195 mm              | 205 mm                     |
|	4    | 6,5 Inch          | 185 mm                    | 195 of 205 mm              | 215 mm                     |
|	5    | 7,0 Inch          | 195 mm                    | 205 of 215 mm              | 225 mm                     |
|	6    | 7,5 Inch          | 205 mm                    | 215 of 225 mm              | 235 mm                     |
|	7    | 8,0 Inch          | 215 mm                    | 225 of 235 mm              | 245 mm                     |
|	8    | 8,5 Inch          | 225 mm                    | 235 of 245 mm              | 255 mm                     |
|	9    | 9,0 Inch          | 235 mm                    | 245 of 255 mm              | 265 mm                     |
|	10   | 9,5 Inch          | 245 mm                    | 255 of 265 mm              | 275 mm                     |
|	11   | 10,0 Inch         | 255 mm                    | 265 of 275 mm              | 285 mm                     |
|	12   | 10,5 Inch         | 265 mm                    | 275 of 285 mm              | 295 mm                     |
|	13   | 11,0 Inch         | 275 mm                    | 285 of 295 mm              | 305 mm                     |
|	14   | 11,5 Inch         | 285 mm                    | 295 of 305 mm              | 315 mm                     |
|	15   | 12,0 Inch         | 295 mm                    | 305 of 315 mm              | 325 mm                     |
|	16   | 12,5 Inch         | 305 mm                    | 315 of 325 mm              | 335 mm                     |
+--------+-------------------+---------------------------+----------------------------+----------------------------+



*/