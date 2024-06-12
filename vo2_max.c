#include <math.h>
#include <stdio.h>


//preconditions: takes in minutes (integer) and seconds (integer)
//postconditions: returns a floating-point number which indicates the user's VO2 max value
float vo2_form (float mile_time){
  double velocity = 1609.34/mile_time;
  double vo2_max = (-4.60 + 0.182258 * velocity + 0.000104 * pow(velocity, 2))/(0.8 + 0.1894393 * exp(-0.012778 * mile_time) + 0.2989558 * exp(-0.1932605 * mile_time));
  return vo2_max;
} // vo2_form(mile_time)

//preconditions: takes in the maximum heart rate (an integer), and the percentage of the max heart rate as an integer
//postconditions: returns the pace per mile in which the effort of the exercise corresponds
float pace_calculate (int percentage, float mile_time) {
  float vVO2max = 1609.34/mile_time;
  float ppm = 1609.34/((percentage * 0.1) * vVO2max);
  
  return ppm;
} // pace_calculate(percentage, mile_time)

//preconditions: takes in the percentage of the max heart rate (integer) and the individual's max heart rate.   
//postconditions: returns the heart rate to which the effort of the exercise corresponds. 
int hr_calculate (int percentage, int max_HR) {
  int hr_zone = max_HR * (percentage * 0.1);
 
  return hr_zone;
} // hr_calculate(percentage, max_HR)

int main(void){

  float mile_time, mins, secs, decimal_num;
  int max_hr, age; 
  
  //prompts the user for their age
  printf("Enter Age: ");
  scanf("%d", &age);
  
  //checks that the input is a valid age for the test
  if (age <= 0 || age >= 100)
    {printf("Input Error: input should be greater than 0 and less the 100\n");
      return 0;}
  
  max_hr = 220 - age; //updates the Max HR based upon the given age from the user

  //prompts user for their personal best in the 1.5 mile running test
  printf("Enter time ran for 1 mile\n");
  printf("Enter minutes: ");
  scanf("%f", &mins);
  printf("Enter secs: ");
  scanf("%f", &secs);

  //converts mile time into all minutes
  mile_time = mins + secs/60; 
  
  //checks that the mins and secs are intputted correctly and are not out of bounds
  if (mile_time <= 0)
    {printf("Input Error: input for minutes should be greater than 0 and input for seconds should be less than 60\n");
      return 0;}
  else
    //prints the user's current VO2 max value
    {printf("Your current VO2 max is: %.2lf\n", vo2_form(mile_time));}

  //prints table that showcases the appropriate paces you should run for the respective effort level
  int zone = 1;
  
  printf("Suggested pace zones based upon your max heart rate and VO2 max:\n");
  printf("        Zone               Pace Per Mile           Heart Rate\n");

  for(int i = 5; i < 10; i++)
    {
      switch (zone){
      case 1:
        printf("\033[1;30;47mWarm-Up Zone:         \033[0m ");
        break;
      case 2:
        printf("\033[1;37;44mEasy Zone:            \033[0m ");
        break;
      case 3:
        printf("\033[1;37;42mModerate/Aerobic Zone:\033[0m ");
        break;
      case 4:
        printf("\033[1;37;43mHard/Lactic Threshold:\033[0m ");
        break;
      case 5:
        printf("\033[1;37;41mMaximum/VO2 Max:      \033[0m ");
        break;
      }
      int lwhole = (int) pace_calculate(i, mile_time);
      int hwhole = (int) pace_calculate(i + 1, mile_time); 
      int ldeci = (pace_calculate(i, mile_time) - lwhole) * 60;
      int hdeci = (pace_calculate(i + 1, mile_time) - hwhole) * 60;  

      printf("%d:%.2d - %d:%.2d mins/mile", lwhole, ldeci, hwhole, hdeci);
      zone += 1;
      printf("%10.2d - %.2d\n", hr_calculate(i, max_hr), hr_calculate(i + 1, max_hr));
    }

  return 0;
}
