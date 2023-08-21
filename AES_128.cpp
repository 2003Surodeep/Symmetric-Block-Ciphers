#include<iostream>
#include<unordered_map>
#include<string>
#include<string.h>
#include<vector>
#include<math.h>
#include<algorithm>
#include<cctype>
using namespace std;

unordered_map<char, string> BIN = { {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6',"0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'a', "1010"}, {'b', "1011"}, {'c', "1100"},{'d',"1101"}, {'e',"1110"}, {'f', "1111"} };
unordered_map<string, char> HEX = { {"0000", '0' }, { "0001", '1' }, { "0010", '2' }, { "0011", '3' }, { "0100",'4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'}, {"1000", '8'}, {"1001", '9'}, {"1010", 'a'}, {"1011", 'b'}, {"1100", 'c'}, {"1101", 'd'}, {"1110", 'e'}, {"1111", 'f'} };

string s_box[16][16] = {																															//substitution box matrix
	{"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
	{"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
	{"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
	{"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
	{"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
	{"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
	{"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
	{"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
	{"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
	{"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
	{"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
	{"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
	{"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
	{"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
	{"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
	{"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"}
};

string inv_s_box[16][16] = {																														//inverse substitution box matrix
	{"52", "09", "6a", "d5", "30", "36", "a5", "38", "bf", "40", "a3", "9e", "81", "f3", "d7", "fb"},
	{"7c", "e3", "39", "82", "9b", "2f", "ff", "87", "34", "8e", "43", "44", "c4", "de", "e9", "cb"},
	{"54", "7b", "94", "32", "a6", "c2", "23", "3d", "ee", "4c", "95", "0b", "42", "fa", "c3", "4e"},
	{"08", "2e", "a1", "66", "28", "d9", "24", "b2", "76", "5b", "a2", "49", "6d", "8b", "d1", "25"},
	{"72", "f8", "f6", "64", "86", "68", "98", "16", "d4", "a4", "5c", "cc", "5d", "65", "b6", "92"},
	{"6c", "70", "48", "50", "fd", "ed", "b9", "da", "5e", "15", "46", "57", "a7", "8d", "9d", "84"},
	{"90", "d8", "ab", "00", "8c", "bc", "d3", "0a", "f7", "e4", "58", "05", "b8", "b3", "45", "06"},
	{"d0", "2c", "1e", "8f", "ca", "3f", "0f", "02", "c1", "af", "bd", "03", "01", "13", "8a", "6b"},
	{"3a", "91", "11", "41", "4f", "67", "dc", "ea", "97", "f2", "cf", "ce", "f0", "b4", "e6", "73"},
	{"96", "ac", "74", "22", "e7", "ad", "35", "85", "e2", "f9", "37", "e8", "1c", "75", "df", "6e"},
	{"47", "f1", "1a", "71", "1d", "29", "c5", "89", "6f", "b7", "62", "0e", "aa", "18", "be", "1b"},
	{"fc", "56", "3e", "4b", "c6", "d2", "79", "20", "9a", "db", "c0", "fe", "78", "cd", "5a", "f4"},
	{"1f", "dd", "a8", "33", "88", "07", "c7", "31", "b1", "12", "10", "59", "27", "80", "ec", "5f"},
	{"60", "51", "7f", "a9", "19", "b5", "4a", "0d", "2d", "e5", "7a", "9f", "93", "c9", "9c", "ef"},
	{"a0", "e0", "3b", "4d", "ae", "2a", "f5", "b0", "c8", "eb", "bb", "3c", "83", "53", "99", "61"},
	{"17", "2b", "04", "7e", "ba", "77", "d6", "26", "e1", "69", "14", "63", "55", "21", "0c", "7d"}
};

string mixColMat[4][4] = {																															//mix columns matrix
	{"02", "03", "01", "01"},
	{"01", "02", "03", "01"},
	{"01", "01", "02", "03"},
	{"03", "01", "01", "02"}
};

string invMixColMat[4][4] = {																														//inverse of the mix columns matrix
	{"0e", "0b", "0d", "09"},
	{"09", "0e", "0b", "0d"},
	{"0d", "09", "0e", "0b"},
	{"0b", "0d", "09", "0e"}
};

string round_constant[] = {																															//round constant array
	"01000000", "02000000", "04000000", "08000000", "10000000", "20000000", "40000000", "80000000", "1b000000", "36000000"
};

string lower(string s) {																															//converts a string to lower case
	string res = "";
	for (int i = 0; i < s.length(); i++) res += tolower(s[i]);
	return res;
}

string left_shift(string w, int n) {																												//left shift a binary string by n bits
	string temp = w + w;
	return temp.substr(n, w.length());
}

string right_shift(string w, int n) {																												//right shift a binary string by n bits
	string temp = w.substr(w.length() - n, n) + w.substr(0, w.length() - n);
	return temp;
}

int zo(char x) {																																	//binary character to integer conversion
	return (x == '1') ? 1 : 0;
}

string toBin(int n) {																																//converts from decimal to binary
	string res = "";
	while (n > 0) {
		if (n % 2 == 0) res += '0';
		else res += '1';
		n /= 2;
	}
	reverse(res.begin(), res.end());
	return res;
}

string BintoHex(string s) {																															//converts a binary string to hex
	string tempstr = s, hexstr = "";
	if (s.length() % 4 != 0) {
		while (tempstr.length() % 4 != 0) {
			tempstr = '0' + tempstr;
		}
	}
	for (int i = 0; i < tempstr.length(); i += 4) {
		string temp = "";
		temp += tempstr[i]; temp += tempstr[i + 1]; temp += tempstr[i + 2]; temp += tempstr[i + 3];
		hexstr += HEX[temp];
	}
	return hexstr;
}

string HextoBin(string s) {																															//converts a hex string to binary
	string binstr = "";
	for (int i = 0; i < s.length(); i++) {
		binstr += BIN[s[i]];
	}
	return binstr;
}

int deci(string bin) {																																//converts from binary to decimal
	int val = 0;
	for (int i = bin.length() - 1; i >= 0; i--) {
		val += zo(bin[i]) * (int)(pow(2, (bin.length() - i - 1)));
	}
	return val;
}

string XOR(string str1, string str2) {																												//performs exclusive-or of two binary strings
	int len = (str1.length() > str2.length()) ? str1.length() : str2.length();
	string tstr1 = str1, tstr2 = str2;
	if (str1.length() < len) {
		string temp = "";
		for (int i = 0; i < len - str1.length(); i++) temp += '0';
		tstr1 = temp + tstr1;
	}
	else {
		string temp = "";
		for (int i = 0; i < len - str2.length(); i++) temp += '0';
		tstr2 = temp + tstr2;
	}
	string res = "";
	for (int i = 0; i < len; i++) {
		res += to_string(zo(tstr1[i]) ^ zo(tstr2[i]));
	}
	return res;
}

string bin2Div(string dividend, string divisor) {																									//performs mod 2 division of 2 binary strings and returns the remainder as a binary string
	int counter = divisor.length();
	string result = XOR(divisor, dividend.substr(0, divisor.length()));
	while (counter < dividend.length()) {
		string temp = result.substr(1, divisor.length() - 1); temp += dividend[counter];
		if (result[1] == '1') result = XOR(temp, divisor);
		else result = XOR(temp, "0");
		counter++;
	}
	return result.substr(result.length() - divisor.length() + 1, divisor.length());
	;
}

string bin2mul(string multiplicand, string multiplier) {																							//performs mod 2 multiplication of 2 binary strings and reduces the product using the irreducible polynomial x8+x4+x3+x+1 if it is larger than 255 and returns the product as a binary string
	string res = "0";																																
	int i = multiplier.length() - 1;
	while (i >= 0) {
		res = XOR(res, toBin((deci(multiplicand)) * zo(multiplier[i]) * (int)pow(2, multiplier.length() - i - 1)));
		i--;
	}
	if (deci(res) > 255) res = bin2Div(res, "100011011");
	return res;
}

string g_fun(string w, int round) {																													//transformation function g takes 32 bit binary input
	string rotword = left_shift(w, 8);																												//32 bit rot word generation by left shifting the word by a byte

	string subword = "";

	for (int i = 0; i < 32; i += 8) {																												//32 bit sub word generation
		string row = ""; row += rotword[i]; row += rotword[i + 1]; row += rotword[i + 2]; row += rotword[i + 3];
		int r = deci(row);
		string col = ""; col += rotword[i + 4]; col += rotword[i + 5]; col += rotword[i + 6]; col += rotword[i + 7];
		int c = deci(col);
		string temp = s_box[r][c];
		subword += BIN[temp[0]]; subword += BIN[temp[1]];
	}

	string round_const = HextoBin(round_constant[round]);

	string final = XOR(subword, round_const);																										//generating the final 32 bit string by performing exclusive-or on the sub word and the respective round constant

	return final;
}

vector<vector<vector<string>>> key_expansion(string key) {																							//Key expansion function that takes in as input a 128 bit hexadecimal key and returns a vector constisting of 11 128 bit hexadecimal sub keys
	string tempk = key;
	if (key.length() < 32) for (int i = 0; i < 32 - key.length(); i++) tempk += 'f';																//right padding the key with 'ff' if the length of the key is less than 128 bits (32 nibbles)

	vector<vector<vector<string>>> master;																											//declaring a 3d master vector to hold all the 11 128 bit sub keys (0 through 10) where each subkey is in the form a 2d vector holding 4 32 bit words
		
	vector<vector<string>> sk0;																														//declaring a 2d vector to hold the 4 32 bit words in sub key 0

	for (int i = 0; i < 4; i++) sk0.push_back(vector<string>());																					//filling up the 2d vector
	int k = 0;
	for (int i = 0; i < 32; i += 2) {
		string temp = "";
		temp += tempk[i]; temp += tempk[i + 1];
		sk0[k].push_back(temp);
		k = (k + 1) % 4;
	}

	master.push_back(sk0);																															//pushing into the master vector sub key 0

	int round = 10;
	vector < vector<string>> tempv = sk0;

	for (int i = 0; i < round; i++) {																												//generating the sub keys for 10 rounds
		string temp_word_array[4];
		string new_word_array[4];
		string new_word_sequence = "";

		for (int j = 0; j < 4; j++) {
			string tempstr = ""; tempstr += tempv[0][j]; tempstr += tempv[1][j]; tempstr += tempv[2][j]; tempstr += tempv[3][j];
			temp_word_array[j] = HextoBin(tempstr);
		}

		new_word_array[0] = XOR(g_fun(temp_word_array[3], i), temp_word_array[0]);
		new_word_array[1] = XOR(temp_word_array[1], new_word_array[0]);
		new_word_array[2] = XOR(temp_word_array[2], new_word_array[1]);
		new_word_array[3] = XOR(temp_word_array[3], new_word_array[2]);

		for (int j = 0; j < 4; j++) new_word_sequence += BintoHex(new_word_array[j]);

		vector < vector<string>> temp;
		for (int j = 0; j < 4; j++) temp.push_back(vector<string>());
		int k1 = 0;
		for (int j = 0; j < 32; j += 2) {
			string tempstr = ""; tempstr += new_word_sequence[j]; tempstr += new_word_sequence[j + 1];
			temp[k1].push_back(tempstr);
			k1 = (k1 + 1) % 4;
		}

		master.push_back(temp);
		tempv = temp;
	}

	return master;
}

string aes_encryption(string ptext, string key) {																									//aes encryption function that takes as input a 128 bit plaintext in hex and 128 bit key in hex and returns a 128 bit cipher text in hex
	string temppt = ptext;
	if (ptext.length() < 32) for (int i = 0; i < 32 - ptext.length(); i++) temppt += 'f';															//right padding the plain text with 'f' if length is less than 128 bits (32 nibbles)

	string ptbin = HextoBin(temppt);																												//converting the hex plaintext into a 128 bit binary string

	vector<vector<vector<string>>> master_key = key_expansion(key);																					//storing all the 11 sub keys in a 3d vector

	vector < vector<string> > sk0 = master_key[0];																									//getting sub key 0


	string sk0hex = "";																																//converting hex sk0 matrix into a 128 bit binary string
	int r = 0, c = 0;
	while (c < 4) { sk0hex += sk0[r][c]; r = (r + 1) % 4; if (r == 0) c++; }
	string sk0bin = HextoBin(sk0hex);

	ptbin = XOR(sk0bin, ptbin);																														//perform exclusive-or between the 128 bit plain text and 128 bit sub key 0
	string pthex = BintoHex(ptbin);

	string pt[4][4];																																//converting the 128 bit hex plain text sequence into a 4x4 state array
	r = 0, c = 0;
	for (int i = 0; i < 32; i += 2) {
		string tempstr = ""; tempstr += pthex[i]; tempstr += pthex[i + 1];
		pt[r][c] = tempstr;
		r = (r + 1) % 4;
		if (r == 0) c++;
	}
	
	//operations on the resultant 128 bit plaintext for 10 rounds
	int round = 10;
	string temp[4][4];
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) temp[i][j] = pt[i][j];

	for (int r = 1; r <= round; r++) {
		if (r != 10) {						//for the first 9 rounds, byte substitution, row shifting, mixing columns and adding round key is performed
			//byte substitution
			int i = 0, j = 0;
			while (i < 4) {
				int row = deci(BIN[temp[i][j][0]]); int col = deci(BIN[temp[i][j][1]]);
				temp[i][j] = s_box[row][col];
				j = (j + 1) % 4;
				if (j == 0) i++;
			}

			//row shifting
			int c1 = 0;
			for (int r1 = 1; r1 < 4; r1++) {
				string tempstr = ""; tempstr += temp[r1][c1]; tempstr += temp[r1][c1 + 1]; tempstr += temp[r1][c1 + 2]; tempstr += temp[r1][c1 + 3];
				tempstr = left_shift(tempstr, r1 * 2);
				string tstr = ""; tstr += tempstr[0]; tstr += tempstr[1]; temp[r1][c1] = tstr;
				tstr = ""; tstr += tempstr[2]; tstr += tempstr[3]; temp[r1][c1 + 1] = tstr;
				tstr = ""; tstr += tempstr[4]; tstr += tempstr[5]; temp[r1][c1 + 2] = tstr;
				tstr = ""; tstr += tempstr[6]; tstr += tempstr[7]; temp[r1][c1 + 3] = tstr;
			}

			//mixing columns
			string mulres[4][4] = {
				{"0", "0", "0", "0"},
				{"0", "0", "0", "0"},
				{"0", "0", "0", "0"},
				{"0", "0", "0", "0"}
			};

			for (int i = 0; i < 4; i++) {																											//mod 2 matrix muliplication
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						mulres[i][j] = XOR(mulres[i][j], bin2mul(HextoBin(mixColMat[i][k]), HextoBin(temp[k][j])));
					}
				}
			}

			for (int i = 0; i < 4; i++) { for (int j = 0; j < 4; j++) temp[i][j] = BintoHex(mulres[i][j]); }

			//adding round key
			string pts = "";																														//converting the resulting 4x4 matrix into a 128 bit binary string
			for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) pts += HextoBin(temp[j][i]);

			string keybin = "";																														//converting the round key into a 128 bit binary string
			vector < vector<string>> tv = master_key[r];
			int r2 = 0, c2 = 0;
			while (c2 < 4) { keybin += HextoBin(tv[r2][c2]); r2 = (r2 + 1) % 4; if (r2 == 0) c2++; }

			string result = BintoHex(XOR(pts, keybin));																								//performing exclusive-or between the resultant plain text and the round key

			int r3 = 0, c3 = 0;
			for (int i = 0; i < 32; i += 2) {
				string tempstr = ""; tempstr += result[i]; tempstr += result[i + 1];
				temp[r3][c3] = tempstr;
				r3 = (r3 + 1) % 4;
				if (r3 == 0) c3++;
			}
		}
		else {																																		//for the 10th round, the mixing columns phase is absent
			//byte substitution
			int i = 0, j = 0;
			while (i < 4) {
				int row = deci(BIN[temp[i][j][0]]); int col = deci(BIN[temp[i][j][1]]);
				temp[i][j] = s_box[row][col];
				j = (j + 1) % 4;
				if (j == 0) i++;
			}

			//row shifting
			int c1 = 0;
			for (int r1 = 1; r1 < 4; r1++) {
				string tempstr = ""; tempstr += temp[r1][c1]; tempstr += temp[r1][c1 + 1]; tempstr += temp[r1][c1 + 2]; tempstr += temp[r1][c1 + 3];
				tempstr = left_shift(tempstr, r1 * 2);
				string tstr = ""; tstr += tempstr[0]; tstr += tempstr[1]; temp[r1][c1] = tstr;
				tstr = ""; tstr += tempstr[2]; tstr += tempstr[3]; temp[r1][c1 + 1] = tstr;
				tstr = ""; tstr += tempstr[4]; tstr += tempstr[5]; temp[r1][c1 + 2] = tstr;
				tstr = ""; tstr += tempstr[6]; tstr += tempstr[7]; temp[r1][c1 + 3] = tstr;
			}

			//adding round key
			string pts = "";																														//converting the resulting 4x4 matrix into a 128 bit binary string
			for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) pts += temp[j][i];
			pts = HextoBin(pts);

			string keyhex = "";																														//converting the round key into a 128 bit binary string
			vector < vector<string>> tv = master_key[r];
			int r2 = 0, c2 = 0;
			while (c2 < 4) { keyhex += tv[r2][c2]; r2 = (r2 + 1) % 4; if (r2 == 0) c2++; }
			string keybin = HextoBin(keyhex);

			string result = BintoHex(XOR(pts, keybin));																								//performing exclusive-or between the resultant plain text and the round key

			int r3 = 0, c3 = 0;
			for (int i = 0; i < 32; i += 2) {
				string tempstr = ""; tempstr += result[i]; tempstr += result[i + 1];
				temp[r3][c3] = tempstr;
				r3 = (r3 + 1) % 4;
				if (r3 == 0) c3++;
			}
		}
	}

	string cipher_text = "";																														//generating the 128 bit cipher text as a hex string
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) cipher_text += temp[j][i];

	return cipher_text;
}

string aes_decryption(string ctext, string key) {																									//aes decryption function that takes as input a 128 bit cipher text in hex and 128 bit key in hex and returns a 128 bit plaintext in hex
	string tempct = ctext;
	if (ctext.length() < 32) for (int i = 0; i < 32 - ctext.length(); i++) tempct += 'f';															//right padding the plain text with 'f' if length is less than 128 bits (32 nibbles)

	string ctbin = HextoBin(tempct);																												//converting the hex cipher text into a 128 bit binary string

	vector<vector<vector<string>>> master_key = key_expansion(key);																					//storing all the 11 sub keys in a 3d vector

	vector < vector<string> > sk10 = master_key[10];																								//getting sub key 10


	string sk10hex = "";																															//converting hex sk10 matrix into a 128 bit binary string
	int r = 0, c = 0;
	while (c < 4) { sk10hex += sk10[r][c]; r = (r + 1) % 4; if (r == 0) c++; }
	string sk10bin = HextoBin(sk10hex);

	ctbin = XOR(sk10bin, ctbin);																													//perform exclusive-or between the 128 bit cipher text and 128 bit sub key 10
	string cthex = BintoHex(ctbin);

	string ct[4][4];																																//converting the 128 bit hex cipher text sequence into a 4x4 state array
	r = 0, c = 0;
	for (int i = 0; i < 32; i += 2) {
		string tempstr = ""; tempstr += cthex[i]; tempstr += cthex[i + 1];
		ct[r][c] = tempstr;
		r = (r + 1) % 4;
		if (r == 0) c++;
	}

	//operations on the resultant 128 bit plaintext for 10 rounds
	int round = 10;
	string temp[4][4];
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) temp[i][j] = ct[i][j];

	for (int r = round - 1; r >= 0; r--) {
		if (r != 0) {							//for the first 9 rounds, row shifting, byte substitution, adding round key, mixing columns is performed
			//row shifting
			int c1 = 0;
			for (int r1 = 1; r1 < 4; r1++) {
				string tempstr = ""; tempstr += temp[r1][c1]; tempstr += temp[r1][c1 + 1]; tempstr += temp[r1][c1 + 2]; tempstr += temp[r1][c1 + 3];
				tempstr = right_shift(tempstr, r1 * 2);
				string tstr = ""; tstr += tempstr[0]; tstr += tempstr[1]; temp[r1][c1] = tstr;
				tstr = ""; tstr += tempstr[2]; tstr += tempstr[3]; temp[r1][c1 + 1] = tstr;
				tstr = ""; tstr += tempstr[4]; tstr += tempstr[5]; temp[r1][c1 + 2] = tstr;
				tstr = ""; tstr += tempstr[6]; tstr += tempstr[7]; temp[r1][c1 + 3] = tstr;
			}

			//byte substitution
			int i = 0, j = 0;
			while (i < 4) {
				int row = deci(BIN[temp[i][j][0]]); int col = deci(BIN[temp[i][j][1]]);
				temp[i][j] = inv_s_box[row][col];
				j = (j + 1) % 4;
				if (j == 0) i++;
			}
			
			//adding round key
			string cts = "";																														//converting the resulting 4x4 matrix into a 128 bit binary string
			for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) cts += HextoBin(temp[j][i]);

			string keybin = "";																														//converting the round key into a 128 bit binary string
			vector < vector<string>> tv = master_key[r];
			int r2 = 0, c2 = 0;
			while (c2 < 4) { keybin += HextoBin(tv[r2][c2]); r2 = (r2 + 1) % 4; if (r2 == 0) c2++; }

			string result = BintoHex(XOR(cts, keybin));																								//performing exclusive-or between the resultant cipher text and the round key

			int r3 = 0, c3 = 0;
			for (int i = 0; i < 32; i += 2) {
				string tempstr = ""; tempstr += result[i]; tempstr += result[i + 1];
				temp[r3][c3] = tempstr;
				r3 = (r3 + 1) % 4;
				if (r3 == 0) c3++;
			}

			//mixing columns
			string mulres[4][4] = {
				{"0", "0", "0", "0"},
				{"0", "0", "0", "0"},
				{"0", "0", "0", "0"},
				{"0", "0", "0", "0"}
			};

			for (int i = 0; i < 4; i++) {																											//mod 2 matrix muliplication
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						mulres[i][j] = XOR(mulres[i][j], bin2mul(HextoBin(invMixColMat[i][k]), HextoBin(temp[k][j])));
					}
				}
			}

			for (int i = 0; i < 4; i++) { for (int j = 0; j < 4; j++) temp[i][j] = BintoHex(mulres[i][j]); }
		}
		else {																																		//for the 10th round (0th sub key), the mixing columns phase is absent
			//row shifting
			int c1 = 0;
			for (int r1 = 1; r1 < 4; r1++) {
				string tempstr = ""; tempstr += temp[r1][c1]; tempstr += temp[r1][c1 + 1]; tempstr += temp[r1][c1 + 2]; tempstr += temp[r1][c1 + 3];
				tempstr = right_shift(tempstr, r1 * 2);
				string tstr = ""; tstr += tempstr[0]; tstr += tempstr[1]; temp[r1][c1] = tstr;
				tstr = ""; tstr += tempstr[2]; tstr += tempstr[3]; temp[r1][c1 + 1] = tstr;
				tstr = ""; tstr += tempstr[4]; tstr += tempstr[5]; temp[r1][c1 + 2] = tstr;
				tstr = ""; tstr += tempstr[6]; tstr += tempstr[7]; temp[r1][c1 + 3] = tstr;
			}

			//byte substitution
			int i = 0, j = 0;
			while (i < 4) {
				int row = deci(BIN[temp[i][j][0]]); int col = deci(BIN[temp[i][j][1]]);
				temp[i][j] = inv_s_box[row][col];
				j = (j + 1) % 4;
				if (j == 0) i++;
			}

			//adding round key
			string cts = "";																														//converting the resulting 4x4 matrix into a 128 bit binary string
			for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) cts += temp[j][i];
			cts = HextoBin(cts);

			string keyhex = "";																														//converting the round key into a 128 bit binary string
			vector < vector<string>> tv = master_key[r];
			int r2 = 0, c2 = 0;
			while (c2 < 4) { keyhex += tv[r2][c2]; r2 = (r2 + 1) % 4; if (r2 == 0) c2++; }
			string keybin = HextoBin(keyhex);

			string result = BintoHex(XOR(cts, keybin));																								//performing exclusive-or between the resultant cipher text and the round key

			int r3 = 0, c3 = 0;
			for (int i = 0; i < 32; i += 2) {
				string tempstr = ""; tempstr += result[i]; tempstr += result[i + 1];
				temp[r3][c3] = tempstr;
				r3 = (r3 + 1) % 4;
				if (r3 == 0) c3++;
			}
		}
	}

	string plain_text = "";																															//generating the plain text as a hex string
	for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) plain_text += temp[j][i];

	return plain_text;
}

int main() {
	//cout << aes_encryption("9a2b6f8cde57f14d3e102a5bc976b3ef", "2b7e151628aed2a6abf7158809cf4f3c") << endl;
	//cout << aes_decryption("7514f22ef697933279424e7415cc3c87", "2b7e151628aed2a6abf7158809cf4f3c") << endl;
	while (true) {
		cout << "\nMain Menu: \n1. AES Encryption\n2. AES Decryption\n3. Exit\n" << endl;
		int choice;
		cin >> choice;
		switch (choice) {
		case 1: {
			cout << "Enter a 128 bit (32 character) hex string to be encrypted and a 128 bit (32 character) key respectively: " << endl;
			string ptext, key;
			cin >> ptext >> key;
			if (ptext.length() != 32 or key.length() != 32) { cout << "Plain text and key have to be 32 characters or 128 bits!\n"; break; }
			cout << "Encrypted string in hex: " << aes_encryption(lower(ptext), lower(key)) << endl;
			break;
		}
		case 2: {
			cout << "Enter a 128 bit (32 character) hex string to be decrypted and a 128 bit (32 character) key respectively: " << endl;
			string ctext, key;
			cin >> ctext >> key;
			if (ctext.length() != 32 or key.length() != 32) { cout << "Cipher text and key have to be 32 characters or 128 bits!\n"; break; }
			cout << "Decrypted string in hex: " << aes_decryption(lower(ctext), lower(key)) << endl;
			break;
		}
		case 3:
			exit(0);
			break;
		default:
			cout << "Enter a valid choice!";
		}
	}
}
