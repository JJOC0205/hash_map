

#include "HashMap.hpp"
#include "HashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	first = "";
	numKeys = 0;
	mapSize = 500;
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;
	map = new hashNode *[mapSize];
	for (int i = 0; i < mapSize; i++){
		map[i] = NULL;
	}

}
void hashMap::addKeyValue(string k, string v) {
	int index = getIndex(k);
	bool added = false;
	if (index == -1){
		if (hashfn){
			cout << "add: " << index  << " " << k << endl;
			index = calcHash1(k);
		} else {
			index = calcHash2(k);
		}
		map[index] = new hashNode[mapSize];
		cout << map[index] << endl;
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
			if (collfn){
				hashcoll++;
				index = coll1(index, hashcoll, k);
			} else {
				hashcoll++;
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
	if (hashfn){
		index = calcHash1(k);
		cout << "getIndex: " << index << " " << k << endl;
	} else {
		index = calcHash2(k);
	}
	if ((map[index] != NULL) && (map[index]->keyword == k)){
		return index;
	} else if ((map[index] != NULL) && (map[index]->keyword != k)){
		if (collfn){
			hashcoll++;
			return coll1(index, hashcoll, k);
		} else {
			hashcoll++;
			return coll2(index, hashcoll, k);
		}
	} else {
		return -1;
	}
}

int hashMap::calcHash2(string k){
	int len = k.length();
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
		int index = 0;
		int tmp = mapSize;
		getClosestPrime();
		hashNode **longer_map = new hashNode *[mapSize];
		for(int i = 0; i < mapSize; i++){
			longer_map[i] = NULL;
		}
		//while loop, add key values
		for(int i = 0; i < tmp; i++){
			if (map[i] != NULL){
				if (hashfn){
					index = calcHash1(map[i]->keyword);
				} else {
					index = calcHash2(map[i]->keyword);
				}
				longer_map[index] = map[i];
			}
		}
		delete [] map;
		map = longer_map;
	}
}
int hashMap::coll1(int h, int i, string k) {
	while(((map[h] != NULL) || (map[h]->keyword != k)) && (h < mapSize)){
		collisions++;
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


