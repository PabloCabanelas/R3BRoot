
void landDigi(){

  // Input files
  TString inFile      = "r3bsim.root";
  TString parFile     = "r3bpar.root";

  // Output file         
  TString outFile     = "land_digi.root";

  

  // -----   Timer   --------------------------------------------------------
  TStopwatch timer;
  timer.Start();
  // ------------------------------------------------------------------------

  // -----   Digitization run   -------------------------------------------
  FairRunAna *fRun= new FairRunAna();
  fRun->SetInputFile(inFile);
  fRun->SetOutputFile(outFile);

  // Verbosity Mode level
  // (0=quiet, 1=event level, 2=track level, 3=debug)
  Int_t iVerbose = 0;

  //Connect the Digitization  Task
  R3BLandDigitizer_CFD* land  = new R3BLandDigitizer_CFD(iVerbose);
	double triggerThreshold=0.7;  //[MeV]
	double timeShift=2;						//[ns]
	double amplitudeScaling=0.7;
	land->SetCfdParameters(triggerThreshold, timeShift,amplitudeScaling);			//Use CFD
//	land->SetLeParameters(triggerThreshold);																		//Use LE
  fRun->AddTask(land);

  // Runtime DataBase info
  FairRuntimeDb* rtdb = fRun->GetRuntimeDb();
  FairParRootFileIo*  parIo1 = new FairParRootFileIo();
  parIo1->open(parFile.Data());
  rtdb->setFirstInput(parIo1);
  rtdb->setOutput(parIo1);
  rtdb->saveOutput();

  // Load the Root Geometry
  fRun->LoadGeometry();
  
  // Number of events to process
  Int_t nEvents = 10000;
  
  // -----   Intialise and run   --------------------------------------------
  fRun->Init();

  fRun->Run(0, nEvents);

  // -----   Finish   -------------------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Output file writen:  "    << outFile << endl;
  cout << "Parameter file writen " << parFile << endl;
  cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
  cout << endl;
  // ------------------------------------------------------------------------

}
