#include <iostream>
#include <Magick++.h>
#include "mainwindow.hpp"
#include <QApplication>
#include <cstdlib>
#include <string>

using Magick::Quantum;

int main(int argc, char *argv[])
{   if (argc != 6)
    {
        std::cerr << "You entered wrong number of parameters\n"
                  << "You need enter 5 parameters\nThe first two parameters are names of two images\nThe third parameter is name of output file\n"
                  << "The 4th parameter is steps number\nThe 5th parameter parameter is delay number\n";
     }
    else
    {
        Magick::Image photo1;
        Magick::Image photo2;
        int number;
        int delay;

        // попытка открыть первую картинку
        try
        {
            photo1.read(argv[1]);
        }
        catch(Magick::ErrorBlob & er)
        {
            std::cerr << er.what() << "Name of 1st image is wrong\n";
            return 1;
        }

        // попытка открыть первую картинку
        try
        {
            photo2.read(argv[2]);
        }
        catch(Magick::ErrorBlob & er)
        {
            std::cerr << er.what() << "\nName of 2nd image is wrong\n";
            return 1;
        }

        // проверка числа шагов
        try
        {
            std::stoi(argv[4]);
        }
        catch(std::invalid_argument & er)
        {
            std::cerr << "You shoud enter steps number\n";
            return 1;
        }
        catch(std::out_of_range & er)
        {
            std::cerr << "You entered a very big steps number. Enter again.\n";
            return 1;
        }

        // проверка задержки
        try
        {
            std::stoi(argv[5]);
        }
        catch(std::invalid_argument & er)
        {
            std::cerr << "You should enter delay number\n";
            return 1;
        }
        catch(std::out_of_range & er)
        {
            std::cerr << "You entered a very big delay number. Enter again\n";
            return 1;
        }
        // проверка задержкии и  шагов на не равенство нулю
        if ((std::stoi(argv[4]) > 0) && (std::stoi(argv[5]) > 0))
        {
            number = std::stoi(argv[4]);
            delay = std::stoi(argv[5]);
        }
        else
        {
            std::cerr << "Steps number and delay number can not be 0\n";
            return 1;
        }


        std::list<Magick::Image> Images;
        for (int i = 0; i <= number; i++)
        {   unsigned int steps = OpaqueAlpha/number * i;
            photo1.alpha(steps);
            photo2.composite(photo1,Magick::CenterGravity,Magick::SrcOverCompositeOp);
            Images.push_back(photo2);
        }
        std::for_each (Images.begin(),Images.end(),Magick::animationDelayImage(delay));
        Magick::animateImages(Images.begin(),Images.end());
        Magick::writeImages(Images.begin(),Images.end(),argv[3],true); // argv[3] - имя файла, в который записывается анимация

    }
return 0;
} //main
