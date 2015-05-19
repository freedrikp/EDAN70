#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <string>

class Attributes {
public:
  static constexpr const char* NBR_LINES = "nbrOfLines";
	static constexpr const char* MEAN_LENGTH = "avgLength";
	static constexpr const char* PARALLELL = "parallell";
	static constexpr const char* PERPENDICULAR = "perpendicular";

	Attributes(double nbr_lines, double mean_length, int parallell, int perpendicular);
	double getNbrLines();
	double getMeanLength();
	int getParallell();
	int getPerpendicular();
	double getValueOfAttr(std::string attr);
private:
	double nbr_lines;
	double mean_length;
	int parallell;
	int perpendicular;

};


#endif
