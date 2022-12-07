#ifndef _PERSON_H_
#define _PERSON_H_


class Person {
    private:
        bool wearingHelmet;
        int medical;
        int age;

    public:
        Person(bool, int, int);
        Person();

        void setHelmet(bool);
        void setMedical(int);
        void setAge(int);

        bool getHelmet();
        int getMedical();
        int getAge();
};


#endif //_PERSON_H_
