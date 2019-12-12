#ifndef DAY12_VECTOR_H
#define DAY12_VECTOR_H

#include <vector>
#include <cstdlib>


class Vector : public std::vector<int> {
public:
	Vector(){ }

	Vector(std::initializer_list<int> data){
		for(int d : data){
			push_back(d);
		}
	}

	Vector operator+(const Vector& r){
		Vector v;

		for(int i = 0; i < size(); i++){
			v.push_back((*this)[i] + r[i]);
		}

		return v;
	}

	void operator+=(const Vector& r){
		for(int i = 0; i < size(); i++){
			(*this)[i] += r[i];
		}
	}

	int sum(){
		int sum = 0;

		for(int i : *this){
			sum += i;
		}

		return sum;
	}

	int sumAbs() const{
		int sum = 0;

		for(int i : *this){
			sum += abs(i);
		}

		return sum;
	}

};


#endif //DAY12_VECTOR_H
