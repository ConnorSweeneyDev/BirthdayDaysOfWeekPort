#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <math.h>

int main()
{
    bool AppLoop = true;
    while (AppLoop == true)
    {
        std::map<int, std::vector<std::string>> days;
        for (int d = 0; d < 7; d++)
        {
            days.insert({ d, { } });
        }

        std::string DOB;
        std::string choice;
        std::cout << "Please enter your date of birth.    [DD-MM-YYYY]: "; std::cin >> DOB;
        std::cout << "How many years do you want to calculate? [0-100]: "; std::cin >> choice;

        std::string day = DOB.substr(0, 2);
        std::string month = DOB.substr(3, 2);
        std::string FourDigitYear = DOB.substr(6, 4);
        std::string TwoDigitYear = DOB.substr(8, 2);
        std::string century = DOB.substr(6, 2);
        std::string HorizontalLine = std::string(35, '-');

        double DoubleChoice = std::stod(choice);
        double DoubleDay = std::stod(day);
        double DoubleMonth = std::stod(month);
        double DoubleFourDigitYear = std::stod(FourDigitYear);
        double DoubleTwoDigitYear = std::stod(TwoDigitYear);
        double DoubleCentury = std::stod(century);
        double LeapYearCode = 0;

        const double MonthCodes[13] = { 0, 1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6 };
        const double CenturyCodes[50] = { 6, 4, 2, 0, 6, 4, 2, 0, 6, 4, 2, 0, 6, 4, 2, 0, 6, 4, 2, 0, 6, 4, 2, 0, 6,
                                    4, 2, 0, 6, 4, 2, 0, 6, 4, 2, 0, 6, 4, 2, 0, 6, 4, 2, 0, 6, 4, 2, 0, 6, 4 };
        const std::string DayNames[7] = { "| Saturday  ", "| Sunday    ", "| Monday    ", "| Tuesday   ",
                                    "| Wednesday ", "| Thursday  ", "| Friday    " };

        int repeat = 0;
        while (repeat < DoubleChoice)
        {
            double MonthCode = MonthCodes[(int)DoubleMonth];
            double CenturyCode = CenturyCodes[(int)DoubleCentury];

            if (((int)DoubleFourDigitYear % 4 == 0 && (int)DoubleFourDigitYear % 100 != 0) || (int)DoubleFourDigitYear % 400 == 0)
            {
                LeapYearCode = 1;
            }
            else
            {
                LeapYearCode = 0;
            }

            //the formula is from https://beginnersbook.com/2013/04/calculating-day-given-date/ under "the key value method"
            double F1 = floor(DoubleTwoDigitYear / 4);
            double F2 = floor(F1 + DoubleDay + MonthCode + CenturyCode + DoubleTwoDigitYear);

            if ((DoubleMonth == 1 || DoubleMonth == 2) && LeapYearCode == 1)
            {
                F2--;
            }
            
            int Weekday = (int)F2 % 7;
            days[Weekday].push_back(std::to_string((int)DoubleFourDigitYear));

            DoubleFourDigitYear++;
            DoubleTwoDigitYear++;
            repeat++;
        }
        
        int MaxLength = 0;
        for (auto Day : days)
        {
            int YearCount = Day.second.size();

            if (YearCount > MaxLength)
            {
                MaxLength = YearCount;
            }
        }

        std::string center = std::string(2 * (15 - MaxLength), ' ');
        std::string TableAcross = std::string(5 * MaxLength, '-');
        std::cout << "\n" + center + "The days of the week your past and future birthdays are on are as follows:\n";
        std::cout << center + HorizontalLine + TableAcross + "-";

        if (MaxLength == 0)
        {
            std::cout << "-----\n";
        }
        else
        {
            std::cout << "\n";
        }

        for (auto Day : days)
        {
            int YearCount = Day.second.size();
            std::string DayName = DayNames[Day.first];
            std::string RepeatedText = center + DayName + "| Count = " + std::to_string(YearCount);
            
            double DigitCount = floor(log10(YearCount) + 1);

            if (DigitCount == 2)
            {
                std::cout << RepeatedText + " | Years = ";
            }
            else if (DigitCount == 1)
            {
                std::cout << RepeatedText + "  | Years = ";
            }
            else
            {
                std::cout << RepeatedText + "  | Years = N/A";
            }

            for (std::string Year : Day.second) 
            {
                double DoubleYear = std::stod(Year);
                double YearsDigitCount = floor(log10(DoubleYear) + 1);
                int Num0 = 0;

                if (DoubleYear == 0)
                {
                    Num0 = 3;
                }
                else
                {
                    Num0 = (int)(4 - YearsDigitCount);
                }

                std::string RepeatZero = std::string(Num0, '0');
                std::cout << RepeatZero + Year + " ";
            }

            int spaces = 0;

            if (MaxLength > YearCount)
            {
                spaces = MaxLength - YearCount;
            }
            if (YearCount == 0)
            {
                std::cout << "  ";
                spaces--;
            }

            for (int space = 0; space < spaces; space++)
            {
                std::cout << "     ";
            }
            std::cout << "|\n";
        }

        std::cout << center + HorizontalLine + TableAcross + "-";

        if (MaxLength == 0)
        {
            std::cout << "-----";
        }
        else
        {
            std::cout << "\n";
        }

        while (true)
        {
            std::string again;
            std::cout << center + "Do you want to try another date? (Y/N): "; std::cin >> again;

            if (again.length() == 1)
            {
                char CharAgain = again[0];

                if (std::toupper(CharAgain) == 'N')
                {
                    AppLoop = false;
                    break;
                }
                else if (std::toupper(CharAgain) == 'Y')
                {
                    std::cout << "\n";
                    break;
                }
                else
                {
                    std::cout << center + "That is not a valid option.\n";
                }
            }
            else
            {
                std::cout << center + "That is not a valid option.\n";
            }
        }
    }
}