//
// Copyright (c) 2016-2017 Enrico Kaden & University College London
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#ifndef _RICEDEBIAS_H
#define _RICEDEBIAS_H

#include <array>
#include <cmath>

#include "chebychev.h"
#include "debug.h"

namespace smt {

//
// If you use this software, please cite:
//   Kaden E, Kruggel F, and Alexander DC: Quantitative Mapping of the Per-
//   Axon Diffusion Coefficients in Brain White Matter. Magnetic Resonance in
//   Medicine, 75:1752–1763, 2016.  http://dx.doi.org/10.1002/mrm.25734
//

float ricedebias(float x, float sigma) {
	const float sqrt_m_pi_2 = std::sqrt(M_PI_2);
	const std::array<float, 30> A = {
			6.51611128589265467737e-12f,
			-1.03419241950675527809e-11f,
			-3.68205389386904123323e-11f,
			2.96958362749932445722e-11f,
			1.92482174467429307404e-10f,
			-3.65827544574732343228e-11f,
			-9.37359437136060684614e-10f,
			-3.34682084388860045656e-10f,
			4.26799684155070459772e-9f,
			3.8305201521811565131e-9f,
			-1.82334289610682313627e-8f,
			-2.71714580872751052743e-8f,
			7.35172696094312231764e-8f,
			1.62321225262284822104e-7f,
			-2.83314174011955615155e-7f,
			-8.92406719381178251447e-7f,
			1.07577670450070330888e-6f,
			4.75229781200366735667e-6f,
			-4.31799431160220740476e-6f,
			-0.0000257228887994197433619f,
			0.0000212585684558723250435f,
			0.000149957240665648470262f,
			-0.000160138439034234481584f,
			-0.000970909132815691552202f,
			0.00162186678492076368264f,
			0.0111286619166396220886f,
			-0.0705846118917617784601f,
			0.228378458161891939008f,
			-0.522575481126732252274f,
			0.845938241271928217411f};
	const std::array<float, 30> B = {
			-1.58816139887369230455e-11f,
			-3.31419379094489460547e-11f,
			-6.92544535683032616085e-11f,
			-1.44917855178007884142e-10f,
			-3.03682090092715778291e-10f,
			-6.37322340127498506384e-10f,
			-1.33956028255480140359e-9f,
			-2.82000520587879451599e-9f,
			-5.94626615073077281786e-9f,
			-1.25593945672682067467e-8f,
			-2.65733922327447026833e-8f,
			-5.63253727721671662272e-8f,
			-1.19609478999032006368e-7f,
			-2.54482550503529990938e-7f,
			-5.42510903272471222105e-7f,
			-1.1588969557456163362e-6f,
			-2.48082142497092975954e-6f,
			-5.32217915671778694833e-6f,
			-0.0000114434296054042647533f,
			-0.0000246618371398246610113f,
			-0.0000532754603067505522786f,
			-0.000115369704992861120149f,
			-0.000250466380665951249951f,
			-0.000545168144373780700202f,
			-0.00118977561688468156699f,
			-0.00260365385598515725383f,
			-0.00571366579506870973628f,
			-0.012574462264888433131f,
			-0.0277546919204136305245f,
			0.101693239387338638145f};

	smt::assert(sigma > 0.0f);
	x /= sigma;

	if(x <= sqrt_m_pi_2) {
		x = 0.0f;
	} else if(x <= sqrt_m_pi_2+6.0f) {
		x -= smt::chebeval(std::sqrt(2.0f/3.0f*(x-sqrt_m_pi_2))-1.0f, A);
	} else {
		x -= smt::chebeval(1.0f-2.0f/(x-sqrt_m_pi_2-5.0f), B);
	}

	x *= sigma;

	return x;
}

double ricedebias(double x, double sigma) {
	const double sqrt_m_pi_2 = std::sqrt(M_PI_2);
	const std::array<double, 30> A = {
			6.51611128589265467737e-12,
			-1.03419241950675527809e-11,
			-3.68205389386904123323e-11,
			2.96958362749932445722e-11,
			1.92482174467429307404e-10,
			-3.65827544574732343228e-11,
			-9.37359437136060684614e-10,
			-3.34682084388860045656e-10,
			4.26799684155070459772e-9,
			3.8305201521811565131e-9,
			-1.82334289610682313627e-8,
			-2.71714580872751052743e-8,
			7.35172696094312231764e-8,
			1.62321225262284822104e-7,
			-2.83314174011955615155e-7,
			-8.92406719381178251447e-7,
			1.07577670450070330888e-6,
			4.75229781200366735667e-6,
			-4.31799431160220740476e-6,
			-0.0000257228887994197433619,
			0.0000212585684558723250435,
			0.000149957240665648470262,
			-0.000160138439034234481584,
			-0.000970909132815691552202,
			0.00162186678492076368264,
			0.0111286619166396220886,
			-0.0705846118917617784601,
			0.228378458161891939008,
			-0.522575481126732252274,
			0.845938241271928217411};
	const std::array<double, 30> B = {
			-1.58816139887369230455e-11,
			-3.31419379094489460547e-11,
			-6.92544535683032616085e-11,
			-1.44917855178007884142e-10,
			-3.03682090092715778291e-10,
			-6.37322340127498506384e-10,
			-1.33956028255480140359e-9,
			-2.82000520587879451599e-9,
			-5.94626615073077281786e-9,
			-1.25593945672682067467e-8,
			-2.65733922327447026833e-8,
			-5.63253727721671662272e-8,
			-1.19609478999032006368e-7,
			-2.54482550503529990938e-7,
			-5.42510903272471222105e-7,
			-1.1588969557456163362e-6,
			-2.48082142497092975954e-6,
			-5.32217915671778694833e-6,
			-0.0000114434296054042647533,
			-0.0000246618371398246610113,
			-0.0000532754603067505522786,
			-0.000115369704992861120149,
			-0.000250466380665951249951,
			-0.000545168144373780700202,
			-0.00118977561688468156699,
			-0.00260365385598515725383,
			-0.00571366579506870973628,
			-0.012574462264888433131,
			-0.0277546919204136305245,
			0.101693239387338638145};

	smt::assert(sigma > 0.0);
	x /= sigma;

	if(x <= sqrt_m_pi_2) {
		x = 0.0;
	} else if(x <= sqrt_m_pi_2+6.0) {
		x -= smt::chebeval(std::sqrt(2.0/3.0*(x-sqrt_m_pi_2))-1.0, A);
	} else {
		x -= smt::chebeval(1.0-2.0/(x-sqrt_m_pi_2-5.0), B);
	}

	x *= sigma;

	return x;
}

} // smt

#endif // _RICEDEBIAS_H
