

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
	if (index == -1){
		if (hashfn){
			index = calcHash1(k);
		} else {
			index = calcHash2(k);
		}
		map[index] = new hashNode(k);
	}
	if (map[index] == NULL){
		map[index] = new hashNode(k, v);
	} else if (map[index]->keyword == k){
		map[index]->addValue(v);
		numKeys--;
	}
	numKeys++;
	if ((numKeys / mapSize) >= 0.7){
		reHash();
	}
}
int hashMap::getIndex(string k) {
	int index = 0;
	if (hashfn){
		index = calcHash1(k);
	} else {
		index = calcHash2(k);
	}
	if ((map[index] != NULL) && (map[index]->keyword == k)){
		return index;
	} else if ((map[index] != NULL) && (map[index]->keyword != k)){
		if (collfn) {
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
	int size = mapSize*2;
	bool found = false;
	bool skip = false;
	while (!found) {
		skip = false;
		size++;
		if (size % 2 == 0 || size % 3 == 0){
			continue;
		}
		for (int i = 5; i * i <= size; i = i + 6){
			if (size % i == 0 || size % (i + 2) == 0){
				skip = true;
				break;
			}
		}
		if (skip == true){
			continue;
		}
		found = true;
		mapSize = size;
	}
}
void hashMap::reHash() {
	if(numKeys/mapSize >= .70){
		int tmp = mapSize;
		hashNode **tmpmap = map;
		getClosestPrime();
		hashNode **longer_map = new hashNode *[mapSize];
		for(int i = 0; i < mapSize; i++){
			longer_map[i] = NULL;
		}
		map = longer_map;
		for(int i = 0; i < tmp; i++){
			if (tmpmap[i] != NULL){
				for (int j = 0; j < tmpmap[i]->currSize; j++){
					if (tmpmap[i]->values[j] != ""){
						addKeyValue(tmpmap[i]->keyword, tmpmap[i]->values[j]);
					}
				}
			}
		}
		delete [] tmpmap;
	}
}
int hashMap::coll1(int h, int i, string k) {
	while((map[h] != NULL) && (map[h]->keyword != k) && (h < mapSize)){
		collisions++;
		h++;
	}
	return h;

}
int hashMap::coll2(int h, int i, string k) {
	double count = 0.0;
	while((map[h] != NULL || (map[h]->keyword != k)) && (h < mapSize)){
		h = (int)(h + pow(count,count))% mapSize;
		collisions++;
		count++;
	}
	return h;
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


