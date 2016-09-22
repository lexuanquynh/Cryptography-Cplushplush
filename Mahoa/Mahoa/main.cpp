#include <iostream>
#include <conio.h>
#include "HillAlgorithms.h"

/*Demo chưa có test thuật toán mã hóa cổ điển Hill
tác giả: quynhbkhn
website: http://controvl.com/
Group: https://www.facebook.com/groups/learningcplusplus
Page: https://www.facebook.com/laptrinhvuilam
Hà Nội ngày 21/9/2016
*/
int main()
{
	HillAlgorithms hill;

	std::string planText = "anhyeuemm";
	std::string cipherText = "JHKIKUMUO";

	hill.Encrypt(planText);
	hill.Decrypt(cipherText);

	getch();
	return 0;
}