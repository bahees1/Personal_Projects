//------------------------------------
//Unit Converter using LCD and Keypad
//Sarujan Baheerathan
//Aug 19, 2024
//------------------------------------

//include library for keypad
#include <Keypad.h>

//include library for LCD
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


//declare how many rows and col on keypad
const char number_of_rows = 4;
const char number_of_col = 4;

//declare which pins are being used for the rows and col
char row_pins[number_of_rows] = {2, 3, 4, 5};
char col_pins[number_of_col] = {6,7,8,9};

//specify what char can be found on the keypad
char key_array[number_of_rows][number_of_col] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
    };

//variable declarations
int i = 0;
char k_pressed = 0;


//screen variables
const int num_of_screens = 3;
int curr_screen = 0;

String screens[num_of_screens][2] = {{"Select Mode", "Press B->"}, {"Ft: ","Yards: "}, {"Yards: ", "Ft: "}};

//int array hold the value entered by the user
String parameters[num_of_screens];
float converted_parameters[num_of_screens];



//create a object keypad
Keypad k1 = Keypad(makeKeymap(key_array), row_pins, col_pins, number_of_rows, number_of_col);

void setup()
{
  Serial.begin(9600);
  // initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
  lcd.setBacklight(HIGH);


}

void loop()
{
  //1 check button input(key_pressed)
  k_pressed = check_KeyPressed();

  //2 change screen based on initial key press(find the screen to print)
  change_screen(k_pressed);

  //3 change screen based on input(print screen)
  print_screen();
  
}

char check_KeyPressed()
{
  //find which key was pressed
  char key_pressed = k1.getKey();
  return key_pressed;
}

void change_screen(char key)
{
  //take in current key and process the action

  //if move screen to the left(check if A was pressed)
  if(key == 'A')
  {
    if(curr_screen == 0)
    {
      curr_screen = num_of_screens - 1;
    }
    else
    {
      curr_screen--;
    }
  }
  //if move screen to the right(check if B was pressed)
  else if(key == 'B')
  {
    if(curr_screen == num_of_screens -1)
    {
      curr_screen = 0;
    }
    else
    {
      curr_screen++;
    }
  }

  //else take in user input and store in parameters
  else if(key >= '0' && key <= '9')
  {
    parameters[curr_screen] += key;


  }

  //pressing enter to start conversion
  else if(key == 'C')
  {
    //call conversion function
    conv_func();



  }





  //clear input
  else if(key == 'D')
  {
    parameters[curr_screen] = "";
    converted_parameters[curr_screen] = 0;

  }




}


void conv_func()
{
  String str = parameters[curr_screen];
  float conv_val = 0;

  //if on Screen 1(Ft -> Yards)
  if(curr_screen == 1)
  {
    //1. convert str to int
    conv_val = str.toFloat();


    //2. calculate conversion (divide by 3)
    conv_val = conv_val / 3;


    //3. store in converted param
    converted_parameters[curr_screen]  = conv_val;


  }
  


  //else if on Screen 2(Yards -> Ft)
  else if(curr_screen == 2)
  {
    //1. convert str to int
    conv_val = str.toFloat();


    //2. calculate conversion (multiply by 3)
    conv_val = conv_val * 3;


    //3. store in converted param
    converted_parameters[curr_screen]  = conv_val;


  }

}






void print_screen()
{
  lcd.clear();
  lcd.print(screens[curr_screen][0]);
  lcd.print(parameters[curr_screen]);
  lcd.setCursor(0, 1);
  lcd.print(screens[curr_screen][1]);
  if(curr_screen > 0)
  {
    lcd.print(converted_parameters[curr_screen]);
  }
  


}










 







