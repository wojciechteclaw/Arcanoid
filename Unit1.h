//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *tlo;
        TImage *paddle;
        TImage *barrier2;
        TImage *barrier1;
        TImage *block1;
        TImage *block2;
        TImage *corona;
        TTimer *mainTimer;
        TTimer *gora;
        TTimer *dol;
        TLabel *score;
        TButton *nextRound;
        TButton *reset;
        TLabel *winner;
        TButton *zakoncz;
        TButton *kontynuacja;
        void __fastcall mainTimerTimer(TObject *Sender);
        void __fastcall nextRoundClick(TObject *Sender);
        void __fastcall zakonczClick(TObject *Sender);
        void __fastcall dolTimer(TObject *Sender);
        void __fastcall goraTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall resetClick(TObject *Sender);
        void __fastcall kontynuacjaClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
