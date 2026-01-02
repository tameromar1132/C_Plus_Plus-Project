#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

enum enQuestionLevel { Easy = 1, Mid = 2, Hard = 3, Mix = 4 };
enum enOperationType { Sum = 1, Sub = 2, Mul = 3, Div = 4, mix = 5 };


struct stQuestionList
{
	int NumberofQuestion = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int Number1 = 0;
	int Number2 = 0;
	int RightAnswer = 0;
	int PlayerAnswer = 0;
	bool IsCorrect;
};

struct stQuiz
{

	int NumberofQuestion = 0;
	stQuestionList QuestionList[100];
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	int NumberOfRightAnswer = 0;
	int NumberOfWrongAnswer = 0;
	bool IsPass;
};

int Random(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

int ReadNumber()
{
	int Number = 0;

	cin >> Number;
	return Number;
}

int HowManyQuestion()
{
	int Rounds = 0;

	cout << "How Many Round Do you Want : ";
	cin >> Rounds;
	return Rounds;
}

enQuestionLevel QuestionLevel()
{
	int Level;

	do
	{
		cout << "Enter The Level Of Question 1[Easy], 2[Medium], 3[Hard], 4[Mix] : ";
		cin >> Level;

	} while (Level < 1 || Level >4);

	return (enQuestionLevel)Level;
}

enOperationType OperationType()
{

	int Operation = 0;
	do
	{
		cout << "Enter The Operation Type Of Question 1[Sum], 2[Sub], 3[Mul], 4[Div], 5[Mix] : ";
		cin >> Operation;

	} while (Operation < 1 || Operation > 5);

	return (enOperationType)Operation;
}

enOperationType RandomType()
{
	int Number = 0;
	return (enOperationType)Random(1, 4);


}

enQuestionLevel RandomLevel()
{
	int Number = 0;
	return (enQuestionLevel)Random(1, 4);

}

string GetOperationTypeWord(enOperationType OperationType)
{
	string arrOPType[5] = { "+", "-" , "*" , "/", "Mix" };
	return arrOPType[OperationType - 1];
}

void PrintQuestion(stQuiz& Quiz, int Round)
{
	cout << "\nQuestion [" << Round << "/" << Quiz.NumberofQuestion << "]\n";
	cout << Quiz.QuestionList[Round].Number1 << endl;
	cout << Quiz.QuestionList[Round].Number2 << " " << GetOperationTypeWord(Quiz.QuestionList[Round].OperationType) << endl;
	cout << "_____________________\n";

}

void SetColorforRound(stQuestionList QuestionList)
{
	if (QuestionList.IsCorrect == true)
		system("color 2F");

	else
	{
		cout << "\a";
		system("color 4F");
	}

}

void IsCorrect(stQuiz& Quiz, int Round)
{
	if (Quiz.QuestionList[Round].PlayerAnswer == Quiz.QuestionList[Round].RightAnswer)
	{
		Quiz.QuestionList[Round].IsCorrect = true;
		Quiz.NumberOfRightAnswer++;
		cout << "Caorrect! :)\n";
	}
	else
	{
		Quiz.QuestionList[Round].IsCorrect = false;
		Quiz.NumberOfWrongAnswer++;
		cout << "Wrong :(\n";

	}
	SetColorforRound(Quiz.QuestionList[Round]);
}

void askForQuestion(stQuiz& Quiz)
{
	for (int i = 0; i < Quiz.NumberofQuestion; i++)
	{
		PrintQuestion(Quiz, i);
		Quiz.QuestionList[i].PlayerAnswer = ReadNumber();
		IsCorrect(Quiz, i);
	}
	Quiz.IsPass = Quiz.NumberOfRightAnswer >= Quiz.NumberOfWrongAnswer;

}

int GetAnswer(enOperationType OperationType, int Number1, int Number2)
{
	switch (OperationType)
	{

	case enOperationType::Sum:
		return Number1 + Number2;
		break;
	case enOperationType::Sub:
		return Number1 - Number2;
		break;
	case enOperationType::Mul:
		return Number1 * Number2;
		break;
	default:
		return Number1 / Number2;
		break;

	}

}

stQuestionList GenerateOneQuestion(enQuestionLevel Questionlevel, enOperationType Operation)
{
	stQuestionList Question;
	stQuiz Quiz;
	if (Operation == enOperationType::mix)
	{
		Question.OperationType = RandomType();
	}

	if (Questionlevel == enQuestionLevel::Mix)
	{
		Question.QuestionLevel = RandomLevel();
	}

	switch (Question.QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = Random(1, 10);
		Question.Number2 = Random(1, 10);

		Question.RightAnswer = GetAnswer(Operation, Question.Number1, Question.Number2);
		Question.QuestionLevel = Questionlevel;
		return Question;

	case enQuestionLevel::Mid:
		Question.Number1 = Random(10, 50);
		Question.Number2 = Random(10, 50);
		Question.RightAnswer = GetAnswer(Operation, Question.Number1, Question.Number2);
		Question.QuestionLevel = Questionlevel;
		return Question;



	default:
		Question.Number1 = Random(50, 100);
		Question.Number2 = Random(50, 100);
		Question.RightAnswer = GetAnswer(Question.OperationType, Question.Number1, Question.Number2);
		Question.QuestionLevel = Questionlevel;
		return Question;

	}

}

string Tape(int NumberOfTap)
{
	for (int i = 0; i < NumberOfTap; i++)
	{
		cout << "\t";
	}
	return "";
}

void GenerateExam(stQuiz& Quiz)
{
	for (int Question = 0; Question < Quiz.NumberofQuestion; Question++)
	{
		Quiz.QuestionList[Question] = GenerateOneQuestion(Quiz.QuestionLevel, Quiz.OperationType);
	}

}

string GetQuestionLevelName(enQuestionLevel QuestionLevel)
{
	string arrLevel[4] = { "[Easy]", "[Mid]", "[Hard]", "[Mix]" };
	return arrLevel[QuestionLevel - 1];

}

void PrintQuizResult(stQuiz Quiz)
{
	cout << "\n";
	cout << Tape(2) << "_____________________________________________________________\n\n";

	if (Quiz.IsPass == true)
	{

		cout << Tape(2) << "                       YouPass :)                           \n";
	}
	else
	{


		cout << Tape(2) << "                       YouFail :(                           \n";
	}
	cout << Tape(2) << "_____________________________________________________________\n";
	cout << Tape(2) << "Round Number             : " << Quiz.NumberofQuestion << endl;
	cout << Tape(2) << "The Level Of Question    : " << GetQuestionLevelName(Quiz.QuestionLevel) << endl;
	cout << Tape(2) << "The Operation Type       : " << GetOperationTypeWord(Quiz.OperationType) << endl;
	cout << Tape(2) << "Number Of Right Answer   : " << Quiz.NumberOfRightAnswer << endl;
	cout << Tape(2) << "Number OF Wrong Answer   : " << Quiz.NumberOfWrongAnswer << endl;
	cout << Tape(2) << "_____________________________________________________________\n";



}

void PlayGame()
{
	stQuiz Quiz;
	Quiz.NumberofQuestion = HowManyQuestion();
	Quiz.QuestionLevel = QuestionLevel();
	Quiz.OperationType = OperationType();
	GenerateExam(Quiz);
	askForQuestion(Quiz);
	PrintQuizResult(Quiz);

}

void Reset()
{
	system("color 0F");
	system("cls");

}

void Play()
{
	char PlayAgain = 'Y';
	do {

		Reset();
		PlayGame();
		cout << "Do you Wont Play Again Y(yes) N(No) : ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');




}

int main()
{
	srand((unsigned)time(NULL));
	Play();

	return 0;
}
