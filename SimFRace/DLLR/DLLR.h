#pragma once
#ifdef DLLR_EXPORTS
#define DLLR_API __declspec(dllexport)
#else
#define DLLR_API __declspec(dllimport)
#endif

#include<iostream>
#include <map>
#include <functional>
#include<vector>
#include <algorithm>
#include <Windows.h>
#include <unordered_map>



namespace  DinLR
{


    // ����� ����� ���������

    class DLLR_API Transport {

    public:
        Transport() = delete; // ����������� �� ���������. = delete ������ ������ � ���������. 
        virtual ~Transport() = default;

        virtual void calculateTime(double distance) = 0; // ����� ��� ���������
        virtual int getTypeRace() const = 0;             //��� ����������
        virtual double getDistance() const = 0;          //���������
        virtual void setDistance(double _distanse) = 0;  //����� �������� ���������
        virtual std::string& getName() const = 0;         //���
                      

        int ID{ 0 };    //����� ����������

    protected:

        Transport(const std::string& name, double speed) : name(name), speed(speed) {}; // �����������

        std::string name;
        double speed = 0; // ������� ��������
        double _distance = 0; // ���������� ���������

    };


    // ����� ����� ��� ��������� ����������

    class  DLLR_API GroundTr : public Transport
    {
    public:

        int getTypeRace() const override; // 1 == �������� �����

    protected:

        GroundTr(const std::string& name, double speed) :Transport(name, speed) {};

    };


    //����� �������

    class DLLR_API Camel : public GroundTr
    {
    public:

        Camel(const std::string& name, double speed, double pausa1, double pausa2, double time_move) :GroundTr(name, speed), pausa1(pausa1), pausa2(pausa2), time_move(time_move) {
            ID = 3;
        };

        void calculateTime(double distance) override;
        double getDistance() const  override { return _distance; }
        void setDistance(double _distanse)  override {};
        std::string getName() const  override { return name; }

    protected:

        double pausa1 = 0;
        double pausa2 = 0;
        double time_move = 0;
    };


    //����� ������� ���������

    class DLLR_API CamelSpeed : public GroundTr
    {
    public:

        CamelSpeed(const std::string& name, double speed, double pausa1, double pausa2, double pausa3, double time_move)
            :GroundTr(name, speed), pausa1(pausa1), pausa2(pausa2), pausa3(pausa3), time_move(time_move) {
            ID = 6;
        };

        void calculateTime(double distance) override;
        double getDistance() const  override { return _distance; }
        void setDistance(double _distanse)  override {};
        std::string getName() const  override { return name; }



    protected:

        double pausa1 = 0;
        double pausa2 = 0;
        double pausa3 = 0;
        double time_move = 0;
    };

    //����� �������

    class DLLR_API Kentavr : public GroundTr
    {
    public:

        Kentavr(const std::string& name, double speed, double pausa1, double time_move) :GroundTr(name, speed), pausa1(pausa1), time_move(time_move) {
            ID = 4;
        };

        void calculateTime(double distance) override;
        double getDistance() const  override { return _distance; };
        void setDistance(double _distanse)  override {};
        std::string getName() const  override { return name; }


    protected:

        double pausa1 = 0;
        double time_move = 0;
    };

    //����� ������� ����������

    class DLLR_API Boots : public GroundTr
    {
    public:

        Boots(const std::string& name, double speed, double pausa1, double pausa2, double time_move) :GroundTr(name, speed), pausa1(pausa1), pausa2(pausa2), time_move(time_move) {
            ID = 1;
        };

        void calculateTime(double distance) override;
        double getDistance() const  override { return _distance; }
        void setDistance(double _distanse)  override {};
        std::string getName() const  override { return name; }

    protected:

        double pausa1 = 0;
        double pausa2 = 0;
        double time_move = 0;
    };


    // ����� ����� ��� ���������� ����������

    class DLLR_API AirTr : public Transport
    {
    public:

        int getTypeRace() const override; //2 == ���� �����

    protected:

        AirTr(const std::string& name, double speed) :Transport(name, speed) {};
    private:

    };

    //����� ����� �������

    class DLLR_API AirCarpet : public AirTr
    {
    public:

        AirCarpet(const std::string& name, double speed) :AirTr(name, speed) {
            ID = 7;
        };

        void calculateTime(double distance) override;
        double getDistance() const  override { return _distance; }
        void setDistance(double _distanse)  override {};
        std::string getName() const  override { return name; }

    };

    //����� ���

    class DLLR_API Eigl : public AirTr
    {
    public:

        Eigl(const std::string& name, double speed) :AirTr(name, speed) {
            ID = 5;
        };

        void calculateTime(double distance) override;
        double getDistance() const  override { return _distance; }
        void setDistance(double _distanse)  override { ; }
        std::string getName() const  override { return name; }

    };


    //����� �����

    class DLLR_API Broomstick : public AirTr
    {
    public:


        Broomstick(const std::string& name, double speed) :AirTr(name, speed) {
            ID = 2;
        };

        void calculateTime(double distance) override;
        double getDistance() const  override { return _distance; }
        void setDistance(double _distanse)  override {};
        std::string getName() const  override { return name; }

    };

 
    // ����� �����

    class DLLR_API Race
    {
    public:
        Race(double distanse, int typerace) {

            _distanse = distanse;
            typeRace = typerace;

        }
        ~Race() {};
       
        void createTr(int value); 

        void startRace(); 

        void sortR(); 

        void print(); 

        void printTypeRace() const; 


        void printTransp(); 

        double  getDistance() const; 

        int getCount() const; 

        //void setCount(int value) { countTr = 0; }

        std::string getresultAdd();

    private:

        std::string resulAdd;
        int countTr = 0;
        std::vector< std::shared_ptr<Transport>> reg;
        int typeRace;
        double _distanse = 0;
    };

}
