#include "TimeWords.h"

String TimeWords::preText[2][2] = {{"ES", "SON"}, {"IT'S", "IT'S"}};
String TimeWords::postText[2][1] = {{"EN PUNTO"}, {"O'CLOCK"}};
String TimeWords::articleText[2][2] = {{"LA", "LAS"}, {"", ""}};
String TimeWords::fractionText[2][4] = {{"PASADAS", "BIEN PASADAS", "CASI", "CASI CASI"},{"A LITTLE BIT OVER", "A BIT OVER", "ALMOST", "NEARLY ALMOST"}};
String TimeWords::numbersText[2][12] = {{"UNA", "DOS", "TRES", "CUATRO", "CINCO", "SEIS", "SIETE", "OCHO", "NUEVE", "DIEZ", "ONCE", "DOCE"}, 
                                        {"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE"}};
String TimeWords::numbersModText[2][12] = {{"Y CINCO", "Y DIEZ", "Y CUARTO", "Y VEINTE", "Y VEINTICINCO", "Y MEDIA", "VEINTICINCO PARA", "VEINTE PARA", "UN CUARTO PARA", "DIEZ PARA", "CINCO PARA", ""},
                                            {"FIVE AFTER", "TEN AFTER", "QUARTER PAST", "TWENTY AFTER", "TWENTY-FIVE AFTER", "HALF PAST", "TWENTY-FIVE TO", "TWENTY TO", "QUARTER TO", "TEN TO", "FIVE TO", ""}};

String &TimeWords::getWords(int hour, int minutes, int lang) {
  int h = (hour > 12) ? hour - 12 : hour;
  h = (h == 0) ? 12 : h;
  int mF = ((float) minutes / 5) + 0.5;
  int mFf = minutes % 5;
  if (mF > 6) {
    h++; 
    if (h == 13) h = 1;
  }

  String pT = (h == 1 && mF <= 6) ? preText[lang][0] : preText[lang][1];
  if ((mFf == 3 || mFf == 4) && lang == SPANISH) {pT += " "; pT += fractionText[lang][mFf - 1]; };
  if (mFf > 0 && lang == ENGLISH) {pT += " "; pT += fractionText[lang][mFf - 1]; };
  String aT = (h == 1) ? articleText[lang][0] : articleText[lang][1];
  String nT = numbersText[lang][h - 1];
  String nMT = (mF == 0) ? "" : numbersModText[lang][mF - 1];
  fT = pT;
  fT += " ";
  if (mF > 6 && lang == SPANISH) {fT += nMT; fT += " ";}
  if (mF >= 1 && lang == ENGLISH) {fT += nMT; fT += " ";}
  fT += aT;
  fT += " ";
  fT += nT;
  if (mF <=6 && lang == SPANISH) {fT += " "; fT += nMT;}
  if ((mFf == 1 || mFf == 2) && lang == SPANISH) {fT += " "; fT += fractionText[lang][mFf - 1]; };
  if (minutes == 0) {fT += " "; fT += postText[lang][0];};
  return fT;
}