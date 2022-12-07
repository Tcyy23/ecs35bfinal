#ifndef ECS36B_FINALS_2022_PERSON_H
#define ECS36B_FINALS_2022_PERSON_H


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


#endif //ECS36B_FINALS_2022_PERSON_H
