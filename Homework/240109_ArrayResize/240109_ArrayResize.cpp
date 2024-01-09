#include <iostream>
#include <ConsoleEngine/EngineDebug.h>

class IntArray
{
public:
    IntArray(int _Size)
    {
        ReSize(_Size);
    }

    IntArray(const IntArray& _Other)
    {
        Copy(_Other);
    }

    ~IntArray()
    {
        Release();
    }

    void operator=(const IntArray& _Other)
    {
        Copy(_Other);
    }

    int& operator[](int _Count)
    {
        return ArrPtr[_Count];
    }

    int Num()
    {
        return NumValue;
    }

    void Copy(const IntArray& _Other)
    {
        NumValue = _Other.NumValue;

        ReSize(NumValue);
        for (int i = 0; i < NumValue; i++)
        {
            ArrPtr[i] = _Other.ArrPtr[i];
        }
    }

    void ReSize(int _Size)
    {
        if (_Size <= 0)
        {
            MsgBoxAssert("배열의 크기가 0일수 없습니다");
        }

        int* ArrCopy = new int[NumValue];

        for (int i = 0; i < NumValue; i++)
        {
            ArrCopy[i] = ArrPtr[i];
        }

        if (ArrPtr != nullptr)
        {
            Release();
        }

        ArrPtr = new int[_Size];

        if (_Size > NumValue)
        {
            for (int i = 0; i < NumValue; i++)
            {
                ArrPtr[i] = ArrCopy[i];
            }

            for (int i = NumValue; i < _Size; i++)
            {
                ArrPtr[i] = 0;
            }
        }
        else
        {
            for (int i = 0; i < _Size; i++)
            {
                ArrPtr[i] = ArrCopy[i];
            }
        }
        
        NumValue = _Size;
        delete[] ArrCopy;
    }

    void Release()
    {
        if (nullptr != ArrPtr)
        {
            delete[] ArrPtr;
            ArrPtr = nullptr;
        }
    }

private:
    int NumValue = 0;
    int* ArrPtr = nullptr;
};

int main()
{
    LeakCheck;

    IntArray NewArray = IntArray(5);    // [?][?][?][?][?]

    for (int i = 0; i < NewArray.Num(); i++)
    {
        NewArray[i] = i;    // [0][1][2][3][4]
    }

    NewArray.ReSize(10);    // [0][1][2][3][4][?][?][?][?][?]

    for (int i = 0; i < NewArray.Num(); i++)
    {
        std::cout << NewArray[i] << std::endl;
    }
}