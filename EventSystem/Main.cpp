#include "RegistryEventHandler.h"
#include "RegistryEventPublisher.h"
#include <stdio.h>
#include <iostream>

#include <atlstr.h> //ICD

class Auction {
private :
	int CurrentBestBid = 0;
	int iTargetPrice;
	const char* strItemName;
	int iBestBidderId = 0;
public:
	Auction(int _TargetItemPrice , const char* _ItemName) {
		iBestBidderId = 0;
		iTargetPrice = _TargetItemPrice;
		strItemName = _ItemName;
	}

	//Called from bidder _BidderId to submit _BidValue return true if _BidderId has the best bidder
	bool SubmitBid (int _BidderId, int _BidValue){
		if (_BidValue > CurrentBestBid)
		{
			iBestBidderId = _BidderId;
			CurrentBestBid = _BidValue;
			return true;
		}
		else {
			return false;
		}

	}

	bool IsTheBestBidder(int BidderId) {
		if (BidderId == iBestBidderId)
			return true;
		else
			return false;
	}

	int BestBid() {
		return CurrentBestBid;
	}

};

class Bidder {
private : 
	int iMyCash;
	int iBidderId;
	Auction * TargetAuction;

public :
	Bidder(int _BidderId, int _iCash, Auction* _TargetAuction) {
		iMyCash = _iCash;
		iBidderId = _BidderId;
		TargetAuction = _TargetAuction;
	}

	void Bid() {
		if (!TargetAuction->IsTheBestBidder(iBidderId))
		{
			int iCurrentBestBid = TargetAuction->BestBid();
			if (iMyCash > iCurrentBestBid)
			{
				TargetAuction->SubmitBid(iBidderId, iCurrentBestBid + 1);
				iMyCash -= iCurrentBestBid + 1;
			}
			else
			{
				
			}
		}
	}

};


//crea un'auction target price
//crea un bidder(auction, bidderID,initial cash)

//auction.start()

//switch class
//device class
//evento è costituito da 1 nome "TURN ON" chiama tutti quelli che si sono registrati a TURN ON

//il device si registra inserendo le seguenti informazioni
//deviceX, metodo activate(), "TURN ON"

//lo switch registra 

/*
class SimpleSwitch {
	std::string stSwitchIdentifier;
	bool isPressed = false;

	RegistryEventPublisher<const char*> m_oEventPublisher;
public:
	SimpleSwitch(std::string _stSwitchIdentifier) : stSwitchIdentifier(_stSwitchIdentifier) 
	{
		
		
	};

	void Press() {
		if (isPressed)
		{
			isPressed = false;
		}
		else
			isPressed = true;
		
		m_oEventPublisher.SetPath("PRESS");
		m_oEventPublisher.Raise(std::string("PRESS").c_str()); //ICD check raise input
	}

	void Print() {
		std::cout << "SWITCH [" << stSwitchIdentifier << "] STATUS: [" << isPressed << "]" << std::endl;
		m_oEventPublisher.SetPath("PRINT");
		m_oEventPublisher.Raise(std::string("PRINT").c_str());
		}
};

class SimpleDevice {
	std::string stIdentifier;
	bool isActive = false;
	RegistryEventHandler<SimpleDevice>	m_ActionEvent;
	RegistryEventHandler<SimpleDevice>	m_PrintEvent;


public:
	SimpleDevice(std::string _stIdentifier) : stIdentifier(_stIdentifier) {
		m_ActionEvent.Subscribe(this, &SimpleDevice::Operate, std::string("PRESS").c_str());
		m_PrintEvent.Subscribe(this, &SimpleDevice::Print, std::string("PRINT").c_str());
	};

	void Operate() {
		if (isActive)
			isActive = false;
		else
			isActive = true;
		std::cout << "OPERATE is CALLED on Device " << stIdentifier << std::endl;
	}

	void Print() {
		std::cout << "DEVICE [" << stIdentifier << "] STATUS: [" << isActive << "]"<< std::endl;
	}

};

void TestSimpleDevice() {
	std::cout << EventRegistry::GetSingleton().GetRegistry().size() << std::endl;

	SimpleDevice dev1("Device_1");
	SimpleDevice dev2("Device_2");

	std::cout << EventRegistry::GetSingleton().GetRegistry().size() << std::endl;


	SimpleSwitch s1("Switch_1");
	s1.Print();

	s1.Press();

	s1.Print();
}
*/


class ElevatorSwitch {
	std::string stElevatorSwitchIdentifier;
	int iButtonRequested = 0;
	//bool isPressed = false;

	RegistryEventPublisher<const char*> m_oEventPublisher;
public:
	ElevatorSwitch(std::string _stElevatorSwitchIdentifier) : stElevatorSwitchIdentifier(_stElevatorSwitchIdentifier)
	{
	};

	void Press(int _iButtonRequested) {


		std::string sTmp = std::to_string(_iButtonRequested);
		char const *pcFloor = sTmp.c_str();
		iButtonRequested = _iButtonRequested;

		
		m_oEventPublisher.SetPath("Elevator/PRESS");
		
		m_oEventPublisher.Raise(pcFloor); //ICD check raise input
	}

	void Print() {
		std::cout << "ELEVATOR SWITCH [" << stElevatorSwitchIdentifier << "] Request FLOOR : [" << iButtonRequested << "]" << std::endl;
		//m_oEventPublisher.SetPath("Elevator/PRESS");
		//m_oEventPublisher.Raise(std::string("PRINT").c_str());
	}
};

class Elevator {
	std::string stIdentifier;
	int iFloor = 0;
	bool isActive = false;
	RegistryEventHandler<Elevator,const char *>	m_FloorRequestEvent;
	//RegistryEventHandler<SimpleDevice>	m_PrintEvent;


public:
	Elevator(std::string _stIdentifier) : stIdentifier(_stIdentifier) {
		m_FloorRequestEvent.Subscribe(this, &Elevator::Operate, std::string("Elevator/PRESS").c_str());
		
	};

	void Operate(const char * _iFloor) {
		iFloor = atoi(_iFloor);
		Print();
	
	}

	void Print() {
		std::cout << "ELEVATOR [" << stIdentifier << "] FLOOR: [" << iFloor << "]" << std::endl;
	}

};

void TestElevator() {
	ElevatorSwitch esw1("Elevator_Switch_01");

	Elevator e1("Elevator_01");

	esw1.Press(10);
}

//IDC 

class Bid {
public:
	Bid(int _ID, int _value) : ID(_ID), value(_value) {};
public: int ID;//BidderID
		int value;//Bid Amount

};

class Bidder {
	std::string stBidderIdentifier;
	int BidderID;
	int CashAmount;
	int iButtonRequested = 0;

	AuctionRegistryEventPublisher<Bid> m_oEventPublisher;
public:
	Bidder(std::string _stBidderIdentifier,int _BidderID,int _CashAmount) : 
		stBidderIdentifier(? stBidderIdentifier), BidderID(_BidderID), CashAmount(_CashAmount)
	{
	};

	void TryBid() {
		
		m_oEventPublisher.SetPath("Auction/BID");
		Bid tmpBid(BidderID, CashAmount);
		m_oEventPublisher.Raise(tmpBid); //ICD check raise input
	}

	void Print() {
		std::cout << "Bidder Name [" << stBidderIdentifier << "] Bidder ID : [" << BidderID << "] " << "CashAmount "<< CashAmount << std::endl;
		//m_oEventPublisher.SetPath("Elevator/PRESS");
		//m_oEventPublisher.Raise(std::string("PRINT").c_str());
	}
};



int main()
{
	EventRegistry::CreateInstance();
	//NO mod before this point
	
	//TestSimpleDevice();
	std::cout << "-------------------" << std::endl;
	//TestElevator()
	std::cout << "-------------------" << std::endl;

	return 0;
}