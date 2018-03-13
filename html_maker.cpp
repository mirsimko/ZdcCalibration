#include<iomanip>
#include<iostream>

void html_maker(int RunNumber = 0)
{
//*********************************************************// specify RunNumber & info.
	char trgSetup[50] = {"ZdcCalibration"};
//	char trgSetup[20] = {"pp500production"};
	char typeEnergy[10]={"msimko"};

	TString Trgsetup = "tune_2018 zdcw-bbcveto";
	TString BeamTypeEnergy = "X+X@200GeV";
//*********************************************************
	if(RunNumber < 1e7 || RunNumber >= 1e8) // has to be an 8-digit number
	{
	  using namespace std;
	  cout << "invalid run number ... has to be an 8-digit number" << endl;
	  return;
	}

	int RunYear=int(RunNumber/1000000)-1;
	char root_file_path[200]={"/star/u/msimko/ZDC/ZDC_Calibration"};
	char work_dir[200];	sprintf(work_dir,"%s/run%d.%s.%s",root_file_path,RunYear,trgSetup,typeEnergy);
	char data_file[200];sprintf(data_file,"%s/analysis/%d/%d_gain_ratio.dat",work_dir,RunNumber,RunNumber);
	char html_file[200];sprintf(html_file,"%s/analysis.%d.htm",work_dir,RunNumber);
	cout<<data_file<<endl;
	cout<<html_file<<endl;

	int east_1=0;				int west_1=0;              	
	int east_2=0;               int west_2=0;
	int east_3=0;               int west_3=0;
	int east_sum=0;             int west_sum=0;
	int east_att=0;             int west_att=0;
	double east_ratio_13=0;     double west_ratio_13=0;
	double east_ratio_23=0;     double west_ratio_23=0;
	double east_percentage_1=0; double west_percentage_1=0;
	double east_percentage_2=0; double west_percentage_2=0;
	double east_percentage_3=0; double west_percentage_3=0;

	ifstream ifile;
	ifile.open(data_file,ios::in);if(!ifile){cerr<<"ifile.open failed"<<endl;return 0;}
	ifile>>east_1>>east_2>>east_3>>east_sum>>east_att;
	ifile>>west_1>>west_2>>west_3>>west_sum>>west_att;
	ifile.close();

	east_ratio_13 = double(east_1)/double(east_3);
	east_ratio_23 = double(east_2)/double(east_3);
	east_percentage_1 = double(east_1)/(double(east_1)+double(east_2)+double(east_3));
	east_percentage_2 = double(east_2)/(double(east_1)+double(east_2)+double(east_3));
	east_percentage_3 = double(east_3)/(double(east_1)+double(east_2)+double(east_3));
	west_ratio_13 = double(west_1)/double(west_3);
	west_ratio_23 = double(west_2)/double(west_3);
	west_percentage_1 = double(west_1)/(double(west_1)+double(west_2)+double(west_3));
	west_percentage_2 = double(west_2)/(double(west_1)+double(west_2)+double(west_3));
	west_percentage_3 = double(west_3)/(double(west_1)+double(west_2)+double(west_3));

//*****************************************************************************
// We have every number we need, start to generate html file
//*****************************************************************************
	ofstream ofile;
	ofile.open(html_file,ios::out);
	if(!ofile) {cerr<<"ofile.open failed"<<endl;return 0;}

	ofile<<"<!DOCTYPE HTML>"<<endl;
	ofile<<"<!-- This webpage is craeted by Miroslav Simko -->"<<endl;
	ofile<<"<html>"<<endl;
	ofile<<"<!-- Head msimko --><!-- **************************************** -->"<<endl;
	ofile<<"<head>"<<endl;
	ofile<<"<title>Run"<<RunNumber<<" ZDC</title>"<<endl;
	ofile<<"<style type=\"text/css\">"<<endl;
	ofile<<"body	{color:black;}"<<endl;
	ofile<<"body	{background-color:white;}"<<endl;
	ofile<<"h1 		{color:#9370DB;}"<<endl;
	ofile<<"h1		{text-align:center;}"<<endl;
	ofile<<"h2		{color:#FF8C00;}"<<endl;
	ofile<<"h2		{text-align:left;}"<<endl;
	ofile<<"p.p1	{color:green;"<<endl;
	ofile<<"		 font-size:1.5em;}"<<endl;
	ofile<<"p.p2	{color:blue;"<<endl;
	ofile<<"		 font-size:1em;}"<<endl;
	ofile<<""<<endl;
	ofile<<"table,th,td"<<endl;
	ofile<<"		{border-width:2px;"<<endl;
	ofile<<"		 border-style:solid;"<<endl;
	ofile<<"		 border-color:#6A8A29;}"<<endl;
	ofile<<"th		{background-color:#85AD33;"<<endl;
	ofile<<"		 color:white;}"<<endl;
	ofile<<""<<endl;
	ofile<<"</style>"<<endl;
	ofile<<"</head>"<<endl;
	ofile<<"<!-- Body msimko --><!-- **************************************** -->"<<endl;
	ofile<<"<body>"<<endl;
	ofile<<"<h1><p>Run "<<RunNumber<<" Analysis</p></h1>"<<endl;
	ofile<<"<h2><p>Trgsetup : "<<Trgsetup<<"</p></h2>"<<endl;
	ofile<<"<h2><p>BeamType@Energy : "<<BeamTypeEnergy<<"</p></h2>"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<hr />"<<endl;
	ofile<<"<p class=\"p1\">For the ratio between 3 towers :</p>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_gain_east.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_gain_east.gif\" alt=\""<<RunNumber<<"_gain_east.gif\" width=\"480\" height \"360\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_gain_west.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_gain_west.gif\" alt=\""<<RunNumber<<"_gain_west.gif\" width=\"480\" height \"360\"/></A>"<<endl;
	ofile<<"<p class=\"p1\">The ratio and percentage between 3 towers : </p>"<<endl;
	ofile<<"<p class=\"p1\">percentage = towerX/(tower1+tower2+tower3)</p>"<<endl;
	ofile<<"<!-- Table 2 ---------------------------------------------------- -->"<<endl;
	ofile<<"<table width=\"500\" border=\"1\" bordercolor=\"#000000\" cellspacing=\"0\" cellpadding=\"10\" style=\"border-collapse:collapse;\">"<<endl;
	ofile<<"	<tr>"<<endl;
	ofile<<"		<th rowspan=\"2\">Beam-Direction</th>"<<endl;
	ofile<<"		<th colspan=\"3\">Ratio</th>"<<endl;
	ofile<<"		<th colspan=\"3\">Percentage</th>"<<endl;
	ofile<<"	</tr>"<<endl;
	ofile<<"	<tr>"<<endl;
	ofile<<"		<th>Tower-1</th>"<<endl;
	ofile<<"		<th>Tower-2</th>"<<endl;
	ofile<<"		<th>Tower-3</th>"<<endl;
	ofile<<"		<th>Tower-1</th>"<<endl;
	ofile<<"		<th>Tower-2</th>"<<endl;
	ofile<<"		<th>Tower-3</th>"<<endl;
	ofile<<"	</tr>"<<endl;
	ofile<<"	<tr>"<<endl;
	//************************************************************************* East Ratio & Percentage // xuyifei
	ofile<<setiosflags(ios::fixed)<<setprecision(2)<<endl;
	ofile<<"		<td align=\"center\">East</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_ratio_13<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_ratio_23<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">1.00</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_percentage_1*100<<"%</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_percentage_2*100<<"%</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_percentage_3*100<<"%</td>"<<endl;
	//*************************************************************************
	ofile<<"	</tr>"<<endl;
	ofile<<"	<tr>"<<endl;
	//************************************************************************* West Ratio & Percentage // xuyifei
	ofile<<"		<td align=\"center\">West</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_ratio_13<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_ratio_23<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">1.00</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_percentage_1*100<<"%</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_percentage_2*100<<"%</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_percentage_3*100<<"%</td>"<<endl;
	ofile<<resetiosflags(ios::fixed)<<endl;
	//*************************************************************************
	ofile<<"	</tr>"<<endl;
	ofile<<"</table>"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<p class=\"p1\">Gain of towers are:</p>"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<table width=\"500\" border=\"1\" bordercolor=\"#000000\" cellspacing=\"0\" cellpadding=\"10\" style=\"border-collapse:collapse;\">"<<endl;
	ofile<<"	<tr>"<<endl;
	ofile<<"		<th>Beam-Direction</th>"<<endl;
	ofile<<"		<th>Gain Tower-1</th>"<<endl;
	ofile<<"		<th>Gain Tower-2</th>"<<endl;
	ofile<<"		<th>Gain Tower-3</th>"<<endl;
	ofile<<"		<th>Gain Sum</th>"<<endl;
	ofile<<"		<th>Gain Attenuated</th>"<<endl;
	ofile<<"	</tr>"<<endl;
	ofile<<"	<tr>"<<endl;
	//************************************************************************* East Gain // xuyifei
	ofile<<"		<td align=\"center\">East</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_1<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_2<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_3<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_sum<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<east_att<<"</td>"<<endl;
	//*************************************************************************
	ofile<<"	</tr>"<<endl;
	ofile<<"	<tr>"<<endl;
	//************************************************************************* West Gain // xuyifei
	ofile<<"		<td align=\"center\">West</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_1<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_2<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_3<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_sum<<"</td>"<<endl;
	ofile<<"		<td align=\"center\">"<<west_att<<"</td>"<<endl;
	//*************************************************************************
	ofile<<"	</tr>"<<endl;
	ofile<<"</table>"<<endl;
	ofile<<""<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<!-- Table 2 ---------------------------------------------------- -->"<<endl;
	ofile<<"<hr />"<<endl;
	ofile<<"<p class=\"p1\">For the sum and attenuated signal :</p>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_att.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_att.gif\" alt=\""<<RunNumber<<"_east_att.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_sum.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_sum.gif\" alt=\""<<RunNumber<<"_east_sum.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_att.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_att.gif\" alt=\""<<RunNumber<<"_west_att.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_sum.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_sum.gif\" alt=\""<<RunNumber<<"_west_sum.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<p class=\"p1\">For the individual tower :</p>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_1.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_1.gif\" alt=\""<<RunNumber<<"_east_1.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_2.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_2.gif\" alt=\""<<RunNumber<<"_east_2.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_3.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_3.gif\" alt=\""<<RunNumber<<"_east_3.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_1.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_1.gif\" alt=\""<<RunNumber<<"_west_1.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_2.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_2.gif\" alt=\""<<RunNumber<<"_west_2.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_3.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_3.gif\" alt=\""<<RunNumber<<"_west_3.gif\" width=\"360\" height \"240\"/></A>"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<hr />"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<"<p class=\"p1\">The difference between sum and tow1+tow2+tow3 :</p>"<<endl;
	ofile<<"<br />"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_sum_diff.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_east_sum_diff.gif\" alt=\""<<RunNumber<<"_east_sum_diff.gif\" width=\"480\" height \"360\"/></A>"<<endl;
	ofile<<" <A href=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_sum_diff.gif\">"<<endl;
	ofile<<"<img src=\"./analysis/"<<RunNumber<<"/"<<RunNumber<<"_west_sum_diff.gif\" alt=\""<<RunNumber<<"_west_sum_diff.gif\" width=\"480\" height \"360\"/></A>"<<endl;
	ofile<<"</body>"<<endl;
	ofile<<"<!-- End msimko --><!-- **************************************** -->"<<endl;
	ofile<<"</html>"<<endl;
}
