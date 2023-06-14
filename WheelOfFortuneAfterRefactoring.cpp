#include <string>
#include <vector>

using namespace std;

class Wheel {
public:
	int getTotalPrice(vector<string> strs, string userdata) {
		int result = 0;
		int continueCount = 0;
		int firstChance[MAX_LINE_COUNT] = { 0 };
		int secondChance[MAX_LINE_COUNT] = { -1, -1, -1, -1, -1 };

		for (int i = 0; i < TRY_COUNT_LIMIT; i++) {
			char tryChar = userdata[i];

			if (getPassCount(strs, tryChar) == 0)
			{
				clearMetadata(continueCount, secondChance);
				continue;
			}
			continueCount++;

			result += get2000Dollar(strs, tryChar, secondChance);
			result += get1000Dollar(strs, tryChar, firstChance, secondChance);
			result += get100Dollar(continueCount, getPassCount(strs, tryChar));

			flipCard(strs, tryChar);
		}

		return result;
	}

private:
	int get2000Dollar(vector<string> strs, char tryChar, int secondChance[5]) {
		int result = 0;

		for (int y = 0; y < strs.size(); y++) {
			if (secondChance[y] == -1) continue;

			for (int x = 0; x < strs[secondChance[y]].size(); x++) {
				if (strs[secondChance[y]][x] == tryChar) {
					result += 2000;
					break;
				}
			}
			secondChance[y] = -1;
		}
		return result;
	}

	int get1000Dollar(vector<string> strs, char tryChar, int firstChance[5], int secondChance[5]) {
		int resultPrice = 0;
		for (int y = 0; y < strs.size(); y++) {
			for (int x = 0; x < strs[y].size(); x++) {
				if (strs[y][x] != tryChar) continue;

				if (firstChance[y] == 0 && x == 0) {
					resultPrice += 1000;
					firstChance[y] = 1;
					secondChance[y] = y;
				}
				else if (firstChance[y] == 0 && x != 0) {
					firstChance[y] = 1;
				}
			}
		}
		return resultPrice;
	}

	int getPassCount(vector<string> strs, char tryChar) {
		int result = 0;

		for (int y = 0; y < strs.size(); y++) {
			for (int x = 0; x < strs[y].size(); x++) {
				if (strs[y][x] != tryChar) continue;
				result++;
			}
		}
		return result;
	}

	void flipCard(vector<string> strs, char tryChar) {
		for (int y = 0; y < strs.size(); y++) {
			for (int x = 0; x < strs[y].size(); x++) {
				if (strs[y][x] != tryChar) continue;
				strs[y][x] = '_';
			}
		}
	}

	int get100Dollar(int conCnt, int passCnt) {
		return (conCnt * 100) * passCnt;
	}

	void clearMetadata(int& conCnt, int chance[]) {
		conCnt = 0;
		for (int i = 0; i < MAX_LINE_COUNT; i++) chance[i] = -1;
	}

	const int TRY_COUNT_LIMIT = 26;
	const int MAX_LINE_COUNT = 5;
};