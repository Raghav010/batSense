#include <bits/stdc++.h>


using namespace std;

char symbols[3]={'r','p','s'};



int negateS(int symindex,int tobeat)
{   
    int shifter=-1;
    if(tobeat==1)
        shifter=1;
    return (symindex+shifter+3)%3;
}


int charToix(char sym)
{
    if(sym=='R')
        return 0;
    if(sym=='P')
        return 1;
    if(sym=='S')
        return 2;
}

char ixTchar(int ix)
{
    if(ix==0)
        return 'R';
    if(ix==1)
        return 'P';
    if(ix==2)
        return 'S';
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int stateN;
    cin >> stateN;
    vector<vector<int>> iDFA (stateN,vector<int> (4,0));
    for(int i=0;i<stateN;i++)
    {
        char sym;
        int r,p,s;
        cin >> sym >> r >> p >>s;
        r-=1;
        p-=1;
        s-=1;
        int symix=charToix(sym);
        iDFA[i][0]=symix;
        iDFA[i][1]=r;
        iDFA[i][2]=p;
        iDFA[i][3]=s;
    }
    /*for(int i=0;i<stateN;i++)
    {
        cout << iDFA[i][0] << iDFA[i][1] << iDFA[i][2] << iDFA[i][3] << "\n";
    }*/

    //stores all dfas that beat opponent
    vector<vector<vector<int>>> initialSdfa;

    

    //making a dfa that beats opponent for each initial state
    for(int i=0;i<stateN;i++)
    {
        vector<int> goneThrough (stateN,-1);
        vector<vector<int>> initialDFA;
        int stateC=0;
        int curState=i;
        int dfaDone=0;
        while(1)
        {
            vector<int> state (4,-1);
            goneThrough[curState]=stateC;
            state[0]=negateS(iDFA[curState][0],1); //setting our dfa move that beats opp state
            state[iDFA[curState][0]+1]=stateC+1; //setting our state transition to the next state on opp dfa move
            int curTempState=iDFA[curState][state[0]+1];

            if(goneThrough[curTempState]!=-1)
            {
                state[iDFA[curState][0]+1]=goneThrough[curTempState];
                dfaDone=1;
            }
            initialDFA.push_back(state);
            if(dfaDone==1)
                break;
            curState=curTempState;
            stateC++;
        }
        initialSdfa.push_back(initialDFA);
    }

/*

    for(int i=0;i<stateN;i++)
    {
        for(int m=0;m<initialSdfa[i].size();m++)
        {
            for(int k=0;k<4;k++)
            {
                cout << initialSdfa[i][m][k] << " ";
            }
            cout << "\n";
        }
        cout << "\n\n\n";
    }*/

 

    

    vector<vector<int>> bDFA;

    int sDFAStates;
    int prevsDFAStates=0;

    vector<int> compDFAIX;

    vector<int> bDFAState (4,-1);

    //setting up the vanilla big dfa(combining all the smaller complement DFAs) 
    for(int i=0;i<stateN;i++)
    {
        compDFAIX.push_back(prevsDFAStates);
        sDFAStates=initialSdfa[i].size();
        for(int m=0;m<sDFAStates;m++)
        {
            bDFAState[0]=initialSdfa[i][m][0];
            for(int k=1;k<4;k++)
            {
                if(initialSdfa[i][m][k]!=-1)
                    bDFAState[k]=initialSdfa[i][m][k]+prevsDFAStates;
                else
                    bDFAState[k]=-1;
            }
            bDFA.push_back(bDFAState);
        }
        prevsDFAStates+=sDFAStates;
    }





    //simulating runs with different initial states and adding missing transitions in complement dfas
    int compDFA=0;
    int offset=compDFAIX[compDFA];


    int MaxIters=bDFA.size();

    for(int i=0;i<stateN;i++)
    {
        if(i==compDFA)
            continue;

        int curOppState=i; //denotes indexes of states in iDFA
        int curMyState=0; //denotes indexes of states in compDFA


        int iters=0;
        while(1)
        {
            int curOppSym=iDFA[curOppState][0];
            int curMySym=bDFA[curMyState][0];


            int prevOppState=curOppState;
            curOppState=iDFA[prevOppState][curMySym+1];

            if(bDFA[curMyState][curOppSym+1]==-1) //checking if it was a fail or draw
            {
                bDFA[curMyState][curOppSym+1]=compDFAIX[curOppState];
                break;
            }
            else
            {
                //infinte negative loop detection
                if((negateS(curMySym,1)==curOppSym || curMySym==curOppSym) && curOppState==prevOppState && curMyState==bDFA[curMyState][curOppSym+1])
                {
                    bDFA[curMyState][curOppSym+1]=compDFAIX[curOppState];
                    break;
                }
                curMyState=bDFA[curMyState][curOppSym+1];
            }
            iters++;
            if(iters==MaxIters)
                break;
        }
    }

    for(int i=0;i<stateN;i++)
    {
        if(i==compDFA)
            continue;

        int curOppState=i; //denotes indexes of states in iDFA
        int curMyState=0; //denotes indexes of states in compDFA


        int iters=0;
        while(1)
        {
            int curOppSym=iDFA[curOppState][0];
            int curMySym=bDFA[curMyState][0];


            int prevOppState=curOppState;
            curOppState=iDFA[prevOppState][curMySym+1];

            if(bDFA[curMyState][curOppSym+1]==-1) //checking if it was a fail or draw
            {
                bDFA[curMyState][curOppSym+1]=compDFAIX[curOppState];
                break;
            }
            else
            {
                //infinte negative loop detection
                /*if((negateS(curMySym,1)==curOppSym || curMySym==curOppSym) && curOppState==prevOppState && curMyState==bDFA[curMyState][curOppSym+1])
                {
                    bDFA[curMyState][curOppSym+1]=compDFAIX[curOppState];
                    break;
                }*/
                curMyState=bDFA[curMyState][curOppSym+1];
            }
            iters++;
            if(iters==MaxIters)
                break;
        }
    }


    int bDFASize=bDFA.size();
    //cout << "\n";
    //cout << "\n";
    cout << bDFASize << "\n";
    for(int i=0;i<bDFASize;i++)
    {
        cout << ixTchar(bDFA[i][0]) << " ";
        for(int k=1;k<4;k++)
        {
            if(bDFA[i][k]!=-1)
            {
                cout << bDFA[i][k]+1 << " ";
            }
            else
            {
                cout << 1 << " ";
            }
        }
        cout << "\n";
    }


    
    
    return 0;
}