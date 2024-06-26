#include <stdio.h>
#include <stdbool.h>
#include "xaxidma.h"
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include <stdlib.h>
#include <complex.h>
#include <time.h>
#include <xtime_l.h>
#include <math.h>

#define N 32
#define M 6

XAxiDma AxiDma;

int init_DMA(){
    XAxiDma_Config *CfgPtr;

    int status;
    CfgPtr=XAxiDma_LookupConfig(XPAR_AXI_DMA_0_DEVICE_ID);

    if(!CfgPtr){
        xil_printf("No Config found for %d\r\n",XPAR_AXI_DMA_0_DEVICE_ID);
        return XST_FAILURE;
    }
    status=XAxiDma_CfgInitialize(&AxiDma, CfgPtr);
    if(status!=XST_SUCCESS){
    	xil_printf("Dma Initialization Failed return status 5d\r\n", status);
    }

    if(XAxiDma_HasSg(&AxiDma)){
    	xil_printf("Device configuraton as SG mode\r\n");
    }
return XST_SUCCESS;
}


u32 checkIdle(u32 baseAddress, u32 offset){
	u32 status;
	status=(XAxiDma_ReadReg(baseAddress, offset))& XAXIDMA_IDLE_MASK;
}

int main(){
	XTime tfpgaStart, tfpgaend;


	const float complex FFT_input[M][N]={{
	        -0.010835061103441 + 0*I, -0.387454368552641 + 0*I, -0.279216539922483 + 0*I,  0.415285019690633 + 0*I,  0.298135504714083 + 0*I, -0.376315000184774 + 0*I, -0.341058958356089 + 0*I,  0.343193804962018 + 0*I,  0.375154718561242 + 0*I,
	        -0.303143998350086 + 0*I, -0.407214697761438 + 0*I,  0.261002668306230 + 0*I,  0.434544656897221 + 0*I, -0.215836184072361 + 0*I, -0.456993446429132 + 0*I,  0.168281406661529 + 0*I,  0.474484481593353 + 0*I, -0.118870325252260 + 0*I,
	        -0.486475135400547 + 0*I,  0.067832260980309 + 0*I,  0.494240659817248 + 0*I, -0.017436611082644 + 0*I, -0.494406269237200 + 0*I, -0.037281025770606 + 0*I,  0.498185701438342 + 0*I,  0.068853813449093 + 0*I, -0.460932098801484 + 0*I,
	        -0.234834206213975 + 0*I, 0 + 0*I, 0 + 0*I, 0 + 0*I, 0 + 0*I
	    },
			{
			        -0.071318272332776 + 0*I, -0.445420020838539 + 0*I,  0.097183946802031 + 0*I,  0.447219819595693 + 0*I, -0.345056724016218 + 0*I, -0.266692397930338 + 0*I,  0.474064788344747 + 0*I,  0.032778237841739 + 0*I, -0.491871944705063 + 0*I,
			         0.213162669970810 + 0*I,  0.385161617317606 + 0*I, -0.404642621897181 + 0*I, -0.183521355478050 + 0*I,  0.495990638845005 + 0*I, -0.063478785455249 + 0*I, -0.464394727280527 + 0*I,  0.294772825495841 + 0*I,  0.317642760448390 + 0*I,
			        -0.453400581038259 + 0*I, -0.091601080377104 + 0*I,  0.498402675545565 + 0*I, -0.155597041770029 + 0*I, -0.422863890389597 + 0*I,  0.370547422916566 + 0*I,  0.228600439271532 + 0*I, -0.463127276877442 + 0*I, -0.014777428953114 + 0*I,
			         0.531505460819803 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I
			    },
				{
				        -0.132515267677791 + 0*I, -0.367586684823613 + 0*I,  0.385533856081694 + 0*I,  0.002181104492986 + 0*I, -0.412513754899271 + 0*I,  0.441581512962393 + 0*I, -0.056732510364303 + 0*I, -0.379924621665453 + 0*I,  0.456194053286066 + 0*I,
				        -0.100353325572518 + 0*I, -0.350874310787509 + 0*I,  0.470780688895402 + 0*I, -0.145561713629186 + 0*I, -0.317310037840676 + 0*I,  0.480222772556592 + 0*I, -0.189151871319947 + 0*I, -0.280703456443984 + 0*I,  0.485081237427658 + 0*I,
				        -0.230839182453652 + 0*I, -0.241381112893268 + 0*I,  0.485148905141608 + 0*I, -0.269954760599046 + 0*I, -0.200603449545531 + 0*I,  0.481189253763360 + 0*I, -0.306373156775200 + 0*I, -0.155015196786541 + 0*I,  0.447060349536087 + 0*I,
				        -0.232905722110270 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I
				    },
					{
					        -0.180726271017977 + 0*I, -0.177001505433335 + 0*I,  0.375405105661063 + 0*I, -0.363063788579486 + 0*I,  0.152199034283900 + 0*I,  0.140422281910010 + 0*I, -0.367840993478297 + 0*I,  0.418025991575332 + 0*I, -0.266141392692647 + 0*I,
					        -0.014321130155968 + 0*I,  0.287422734738395 + 0*I, -0.420663749038783 + 0*I,  0.349730220571878 + 0*I, -0.109063399063680 + 0*I, -0.184528627343167 + 0*I,  0.388562389484961 + 0*I, -0.404010153552359 + 0*I,  0.223363300537709 + 0*I,
					         0.066202125786249 + 0*I, -0.324076297760982 + 0*I,  0.425393204617726 + 0*I, -0.321288308974408 + 0*I,  0.062891950672632 + 0*I,  0.222579065892988 + 0*I, -0.391528987834215 + 0*I,  0.347561072909193 + 0*I, -0.104321786213041 + 0*I,
					        -0.322178781301976 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I
					    },
						{
						        -0.187342375226759 + 0*I,  0.036638353378304 + 0*I,  0.121401261229211 + 0*I, -0.236552855500857 + 0*I,  0.292939492269738 + 0*I, -0.293646700827127 + 0*I,  0.243415440706354 + 0*I, -0.152163553483636 + 0*I,  0.035323479010607 + 0*I,
						         0.087760818287194 + 0*I, -0.196760588688353 + 0*I,  0.273732246202270 + 0*I, -0.305817641259900 + 0*I,  0.287705338730396 + 0*I, -0.222361184237055 + 0*I,  0.120515112931829 + 0*I,  0.001088713568359 + 0*I, -0.122413842170120 + 0*I,
						         0.223144268216946 + 0*I, -0.287094585007907 + 0*I,  0.303571505121805 + 0*I, -0.269730236965943 + 0*I,  0.190566097298484 + 0*I, -0.077190723139788 + 0*I, -0.056102001965184 + 0*I,  0.195851059187874 + 0*I, -0.304452187146803 + 0*I,
						         0.388763813006438 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I
						    },{
						            -0.126868342735233 + 0*I,  0.145554211947953 + 0*I, -0.075187060562384 + 0*I,  0.031330335110381 + 0*I, -0.004742297770048 + 0*I, -0.014164493769561 + 0*I,  0.030198736734453 + 0*I, -0.044923637963102 + 0*I,  0.058669509214401 + 0*I,
						            -0.071440209435119 + 0*I,  0.083195208702014 + 0*I, -0.093882792353829 + 0*I,  0.103474399513750 + 0*I, -0.111956695608129 + 0*I,  0.119242685907405 + 0*I, -0.125251922635071 + 0*I,  0.129939015830985 + 0*I, -0.133316784751655 + 0*I,
						             0.135326261158828 + 0*I, -0.135791476936467 + 0*I,  0.134707112326582 + 0*I, -0.132086444949269 + 0*I,  0.128158995288433 + 0*I, -0.123507352874156 + 0*I,  0.118642774821077 + 0*I, -0.110902488799094 + 0*I,  0.085427662959680 + 0*I,
						             0.019132428030044 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I,  0 + 0*I
						        }
	};
	xil_printf("\r\n***Entering main Function\r\n");



	int status_dma=init_DMA();

	if(status_dma!=XST_SUCCESS){
		xil_printf("Couldn't initialize DMA\r\n");
		return XST_FAILURE;
	}

	for(int l=0;l<6;++l){

	float complex RX_PNTR[N];
	Xil_DCacheFlushRange((UINTPTR)FFT_input[l], (sizeof(float complex)*N));
	Xil_DCacheFlushRange((UINTPTR)RX_PNTR,(sizeof(float complex)*N));



xil_printf("\r Starting Data transfer-------->>>>>\r\n");
int status_transfer;


XTime_GetTime(&tfpgaStart);

status_transfer=XAxiDma_SimpleTransfer(&AxiDma,(UINTPTR)FFT_input[l],(sizeof(float complex)*N),XAXIDMA_DMA_TO_DEVICE);
if(status_transfer!=XST_SUCCESS){
	xil_printf("Reading data from FFT via DMA failed\r\n");
}

status_transfer=XAxiDma_SimpleTransfer(&AxiDma, (UINTPTR)RX_PNTR,(sizeof(float complex)*N), XAXIDMA_DEVICE_TO_DMA);
if(status_transfer!= XST_SUCCESS){
	xil_printf("Writing data to FFT_IP via DMA failed\r\n");
}

XTime_GetTime(&tfpgaend);

int status=checkIdle(XPAR_AXI_DMA_0_BASEADDR,0x4);


while(status!=2){

	status=checkIdle(XPAR_AXI_DMA_0_BASEADDR,0x4);
}

status=checkIdle(XPAR_AXI_DMA_0_BASEADDR,0x34);

while(status!=2){

	status=checkIdle(XPAR_AXI_DMA_0_BASEADDR,0x34);
}


//int j=0;
//printf("size of float complex %d \n", sizeof(float complex));
//for (j=0;j<N;j++){
//	printf(" PL output : %f +I%f\n",crealf(RX_PNTR[j]),cimagf(RX_PNTR[j]));
//}

float mag_fft[N];
for(int i=0;i<N;++i){
	if(crealf(RX_PNTR[i])<0)
		if(cimagf(RX_PNTR[i])<0)
			mag_fft[i]=-(crealf(RX_PNTR[i])+cimagf(RX_PNTR[i]));
		else
			mag_fft[i]=(-crealf(RX_PNTR[i])+cimagf(RX_PNTR[i]));
	else
		if(cimagf(RX_PNTR[i])<0)
			mag_fft[i]=(crealf(RX_PNTR[i])-cimagf(RX_PNTR[i]));
		else
			mag_fft[i]=(crealf(RX_PNTR[i])+cimagf(RX_PNTR[i]));


	//printf(" mag fft output : %f \n",mag_fft[i]);

}


int maxIndex = 0; // Assume first element is the maximum initially
    for (int i = 0; i < 32; i++) {
        if (mag_fft[i] > mag_fft[maxIndex]) {
            maxIndex = i; // Update maxIndex if current element is greater
        }
    }


xil_printf("Max index value is %d\r\n",maxIndex);

printf("Distance :%f\r\n",(float)maxIndex*1.332);

	}

xil_printf("\n------------ TIME COMPARISION");


float time_fpga=0;
time_fpga=(float)1.0*(tfpgaend-tfpgaStart)/(COUNTS_PER_SECOND/1000000);
xil_printf("time for PL: %d\n", time_fpga);
return XST_SUCCESS;


}







