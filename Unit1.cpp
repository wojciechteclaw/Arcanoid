//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int x;
int y;
int userPoints = 0;
int coronaPoints = 0;
int barrier1Speed = 3;
int barrier2Speed = 3;

bool clashWithBlock(TImage *barrier, TImage *virus){
        if (virus->Left + virus->Width >= barrier->Left &&
        virus->Left<= barrier->Left + barrier->Width &&
        virus->Top + virus->Height >= barrier->Top &&
        virus->Top <= barrier->Top + barrier->Height){
                return true;
        }
        else return false;
}

bool clashWithBarrier(TImage *barrier, TImage *virus){
        int barrierLeftField = barrier->Left + barrier->Width/2 - 4;
        int barrierRightField =  barrier->Left + barrier->Width/2 + 4;
        int virusMiddlePoint = virus->Left + virus->Width/2;
        if (virusMiddlePoint >= barrierLeftField &&
        virusMiddlePoint<= barrierRightField &&
        virus->Top + virus->Height >= barrier->Top &&
        virus->Top <= barrier->Top + barrier->Height){
                return true;
        }
        else return false;
}

void setScore(TLabel *score, int coronaPoints, int userPoints){
        score->Caption = IntToStr(coronaPoints) + ":" + IntToStr(userPoints);
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mainTimerTimer(TObject *Sender)
{
    corona -> Left += x;
    corona -> Top += y;
    setScore(score, coronaPoints, userPoints);

    //odbij od gornej krawedzi
    if (corona->Top <= tlo->Top){
        y = -y;
    }

    //odbij od dolnej krawedzi
    if (corona->Top + corona->Height >= tlo->Height){
        y = -y;
    }

    //odbij od prawej sciany - temporary
    if (corona->Left + corona->Width >= tlo->Width - 5){
        x = -x;
    }

    //odbij od bariery1
    if (clashWithBarrier(barrier1, corona)){
        x = -x;
    }

    //odbij od bariery2
    if (clashWithBarrier(barrier2, corona)){
        x = -x;
    }

    //odbij od blokady 1
    if (clashWithBlock(block1, corona)){
        x = -x;
    }

    //odbij od blokady 2
    if (clashWithBlock(block2, corona)){
        x = -x;
    }

    //przesun bariere 1
    if (barrier1->Top <= 0 && barrier1Speed < 0){
        barrier1Speed = - barrier1Speed;
    }
    else if (barrier1->Top + barrier1->Height >= tlo->Height && barrier1Speed > 0){
       barrier1Speed = - barrier1Speed;
    }

    else{
        barrier1->Top += barrier1Speed;
    }

    //przesun bariere 2
    if (barrier2->Top <= 0 && barrier2Speed < 0){
        barrier2Speed = - barrier2Speed;
    }
    else if (barrier2->Top + barrier2->Height >= tlo->Height && barrier2Speed > 0){
       barrier2Speed = - barrier2Speed;
    }

    else{
        barrier2->Top += barrier2Speed;

    }

    //punkt dla uzytkownika
    if (corona->Left <= block2->Left || corona->Left <= block1->Left){
        mainTimer -> Enabled = false;
        userPoints += 1;
        setScore(score, coronaPoints, userPoints);
        if (userPoints == 3){
                winner->Caption = "GRATULACJE! Udalo Ci sie pokonac wirusa!";
                winner -> Visible = true;
                reset -> Visible = true;
                zakoncz -> Visible = true;
        }
        else{
                nextRound -> Visible = true;
                reset -> Visible = true;
                zakoncz -> Visible = true;
        }
    }

    //punkt dla coronavirusa
    if (corona->Left + corona->Width > paddle->Left + 10){
        mainTimer -> Enabled = false;
        coronaPoints += 1;
        setScore(score, coronaPoints, userPoints);
        if (coronaPoints == 3){
                winner->Caption = "PORA¯KA! CoronaVirus zainfekowa³ Twój kraj!";
                winner -> Visible = true;
                reset -> Visible = true;
                zakoncz -> Visible = true;
        }
        else{
            nextRound -> Visible = true;
            reset -> Visible = true;
            zakoncz -> Visible = true;
        }
    }

    //odbij od paletki
    if (corona->Left + corona->Width >= paddle->Left &&
    corona->Top + corona->Height/2 >= paddle->Top &&
    corona->Top + corona->Height/2 <= paddle->Top + paddle->Height){
        x = -x;
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
        corona->Left = 150;
        corona->Top =  300;
        nextRound->Visible = false;
        mainTimer -> Enabled = true;
        reset -> Visible = false;
        zakoncz -> Visible = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::zakonczClick(TObject *Sender)
{
        Application -> Terminate();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::dolTimer(TObject *Sender)
{
        if (mainTimer ->Enabled){
                if (paddle->Top + paddle->Height <= tlo->Height){
                        paddle->Top += 10;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::goraTimer(TObject *Sender)
{
        if (mainTimer ->Enabled){
                if (paddle->Top >= 0){
                        paddle->Top -= 10;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_UP) gora->Enabled = true;
    if (Key == VK_DOWN) dol->Enabled = true;
    if (Key == VK_ESCAPE){
        kontynuacja->Visible = true;
        mainTimer->Enabled = false;
        zakoncz -> Visible = true;

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_UP) gora->Enabled = false;
    if (Key == VK_DOWN) dol->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::resetClick(TObject *Sender)
{
        userPoints = 0;
        coronaPoints = 0;
        barrier1Speed = 3;
        barrier2Speed = 3;
        corona->Left = 150;
        corona->Top =  300;
        nextRound->Visible = false;
        mainTimer -> Enabled = true;
        reset -> Visible = false;
        zakoncz -> Visible = false;
        winner->Visible = false;
        mainTimer->Enabled = false;
        Label1->Visible = true;
        mode1->Visible = true;
        mode2->Visible = true;
        mode3->Visible = true;
        setScore(score, coronaPoints, userPoints);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::kontynuacjaClick(TObject *Sender)
{
        kontynuacja->Visible = false;
        mainTimer->Enabled = true;
        zakoncz -> Visible = false;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::mode1Click(TObject *Sender)
{
  y = -4;
  x = -4;
  Label1->Visible = false;
  mainTimer->Enabled = true;
  mode1->Visible = false;
  mode2->Visible = false;
  mode3->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mode2Click(TObject *Sender)
{
  y = -6;
  x = -6;
  Label1->Visible = false;
  mainTimer->Enabled = true;
  mode1->Visible = false;
  mode2->Visible = false;
  mode3->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::mode3Click(TObject *Sender)
{
  y = -8;
  x = -8;
  Label1->Visible = false;
  mainTimer->Enabled = true;
  mode1->Visible = false;
  mode2->Visible = false;
  mode3->Visible = false;

}
//---------------------------------------------------------------------------



