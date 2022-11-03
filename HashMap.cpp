

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
	int index = getIndex(k);
	bool added = false;
	if (index == -1){
		if (hashfn == true){
			index = calcHash1(k);
		} else {
			index = calcHash2(k);
		}
		map[index] = new hashNode(k, v);
		added = true;
	}
	while (!added){
		if (map[index] == NULL){
			map[index] = new hashNode(k, v);
			added = true;
		} else if (map[index]->keyword == k){
			map[index]->addValue(v);
			added = true;
		} else {
			if (collfn == true){
				index = coll1(index, hashcoll, k);
			} else {
				index = coll2(index, hashcoll, k);
			}
		}
	}
	if ((numKeys / mapSize) >= 0.7){
		reHash();
	}
}
int hashMap::getIndex(string k) {
	int index = 0;
	if (hashfn == true){
		index = calcHash1(k);
	} else {
		index = calcHash2(k);
	}
	if (map[index] != NULL){
		return index;
	} else {
		return -1;
	}
}

int hashMap::calcHash2(string k){
	int len = k.length;
	int h = 0;
	for (int i = len - 1; i > 0; i--){
		h = (11*h + (int)k[i]) % mapSize;
	}
	return h;
}
int hashMap::calcHash1(string k){
	int hashed_key = (int)k[0] + ((int)k[1]*27) + ((int)k[2]*729);
	return hashed_key % mapSize;
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

	if(numKeys/mapSize >= .70){
		getClosestPrime();
		int index = 0;
		hashMap **longer_map = new hashMap(map[0],numKeys,mapSize,hashfn,collfn,0,0);
		for(int i = 0; i <mapSize; i++){
			index = hashfn(map[i]);

		}
	}
	delete [] map;
}

int hashMap::coll1(int h, int i, string k) {
	 while((map[h] != NULL || (map[h]->keyword != k)) && (h < mapSize)){
		h++;
	}
	return h;

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


