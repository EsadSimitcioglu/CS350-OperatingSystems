#include <stdio.h>
#include <stdbool.h>
int main(){

	int inputFromTheUser;
	int threshold = 12;
	int foodSize = 5;
	int counter = 0;
	bool isHome = true;
	int shortListSize = 0;
	int tempIndex = -1;
	int max = 0;
	int index = -1;
	int foodList[foodSize];
	int shortList[foodSize];
	int finalShortList[foodSize];
	char foodListName[5][20] = {"Kebab", "Burger", "Pasta", "Lahmacun", "Salad"};
	int numberOfPeople;

	
	printf("How many people did we have : ");
	scanf("%d",&numberOfPeople);
	
	for(int i = 0;i<foodSize;i++)
		foodList[i] = 0;
		
	for(int i = 0;i<foodSize;i++)
		finalShortList[i] = 0;


	for(int i = 0; i<numberOfPeople;i++)
	{
		printf("1-Kebab\n2-Burger\n3-Pasta\n4-Lahmacun\n5-Salad\n");
		printf("User%d\n",(i+1));
		for(int j =foodSize;j>0;j--)
		{
			printf("Enter Your %d. Preference: ",(foodSize-j+1));
        	scanf("%d",&inputFromTheUser);
	        foodList[inputFromTheUser-1] += j;

		}
	}
	
	printf("\n\n\n ***************First Round*************** \n\n\n");
	
	for(int i = 0;i<foodSize;i++)
		printf("%s =>     %d\n",foodListName[i],foodList[i]);
	
	
	for(int i = 0;i<foodSize;i++)
		shortList[i] = foodList[i];
	
	for(int i = 0;i<foodSize;i++){
		if(foodList[i]<threshold)
			shortList[i] = 0;
	}
	
	for(int i = 0;i<foodSize;i++){
		if(shortList[i] != 0){
			isHome = false;
			shortListSize += 1;
			tempIndex = i;
		}
		
	}
	
	
	if(isHome)
		printf("You are eating at home/dorm today\n");
	else if(shortListSize == 1)
		printf("We will eat %s today\n",foodListName[tempIndex]);
	else{
	
		printf("The Short List Is : \n");
		for(int i = 0;i<foodSize;i++){
			if(shortList[i] != 0){
				printf("%d-",i+1);
				puts(foodListName[i]);
			}
		}
		
		printf("Select From The Remaining Foods\n");	
		for(int i = 0; i<numberOfPeople;i++)
		{
			printf("User%d\n",(i+1));
			counter = 0;
			for(int j =foodSize;j>0;j--)
			{
				if(shortList[j-1] == 0){
					continue;
				}
				printf("Enter Your %d. Preference: ",(++counter));
        	    scanf("%d",&inputFromTheUser);
	            finalShortList[inputFromTheUser-1] += j;
			}
		}
		
		printf("\n\n\n ***************Second Round*************** \n\n\n");
					
		for(int i = 0;i<foodSize;i++){
			if(finalShortList[i] > max && shortList[i] != 0){
				max = finalShortList[i];
				index = i;
				printf("%s =>          %d\n",foodListName[i],finalShortList[i]);
			}
		}
		
		printf("We will eat %s today\n",foodListName[index]);
	}
		
	return 0;
}
