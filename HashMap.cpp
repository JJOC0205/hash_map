

#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	first = map[0];
	numKeys = 0;
	mapSize = 500;
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;
	for (int i = 0; i < mapSize; i++){
		map[i] = NULL;
	}
}
void hashMap::addKeyValue(string k, string v) {
}
int hashMap::getIndex(string k) {
}

int hashMap::calcHash2(string k){
	getClosestPrime();
	return k%mapSize;
}
int hashMap::calcHash1(string k){
	getClosestPrime();
	return k%mapSize;
}
void hashMap::getClosestPrime() {
	bool found = false;
	int size = mapSize*2;
	while(!found){
		for (int i = 2; i <= (mapSize); i++){
			if (!(size % i == 0)){
				found = true;
			}
		}
		size++;
	}
	mapSize = size - 1;
}
void hashMap::reHash() {
}
int hashMap::coll1(int h, int i, string k) {
}
int hashMap::coll2(int h, int i, string k) {
}

void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


