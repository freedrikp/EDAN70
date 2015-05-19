#include "attributes.h"

Attributes::Attributes(double nbr_lines, double mean_length, int parallell, int perpendicular): nbr_lines(nbr_lines),mean_length(mean_length),parallell(parallell), perpendicular(perpendicular){}
	

double Attributes::getValueOfAttr(std::string attr)
{
	
	if(attr == Attributes::NBR_LINES){
		return nbr_lines;
	}else if(attr == Attributes::MEAN_LENGTH){
		return mean_length;
	}else if(attr == Attributes::PARALLELL){
		return parallell;
	}else if(attr == Attributes::PERPENDICULAR){
		return perpendicular;
	}else{
		return 0;
	}
}

double Attributes::getNbrLines()
{
	return nbr_lines;
}


double Attributes::getMeanLength()
{
	return mean_length;
}


int Attributes::getParallell()
{
	return parallell;
}


int Attributes::getPerpendicular()
{
	return perpendicular;
}
