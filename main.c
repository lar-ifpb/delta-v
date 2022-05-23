#include <brick.h>
#include <stdio.h>

#define S_COR IN4

#define MOTOR_D OUTA
#define MOTOR_E OUTB
#define DOIS_MOTORES (MOTOR_E | MOTOR_D)

int verificaMotores(){
	if(! tacho_is_plugged(DOIS_MOTORES, LEGO_EV3_L_MOTOR)){
		printf("Algum motor desconectado\n");
		return 0;
	}
	return 1;
}

int verificaSensores(){
	if(! sensor_is_plugged(S_COR, LEGO_EV3_COLOR)){
		printf("sensor desconectado\n");
		return 0;
	}
	if(! color_set_mode_col_reflect(S_COR)){
		printf("erro ao configurar o sensor no modo de reflectancia\n");
		return 0;
	}
	return 1;
}

void lerSuperficie(){
	printf("%f\n",sensor_get_value0(S_COR, 0.0));
	sleep_ms(500);
}

/* Limita valor a valores entre 1 e 0.
 */
double limitar_valor(double valor){
	if (valor > 1)
		return 1;
	else if (valor < 0)
		return 0;
	else
		return valor;
}

void seguir_linha(){
        double valor_sensor,erro,correcao,pot_d,pot_e;
	const double KP = 0.3/34.5;
	const int vel_max = tacho_get_max_speed(MOTOR_D,100);
	const double pot_base = 0.3;
	printf("variaveis inicializadas\n");

	while(1){
		printf("mais um loop\n");
		valor_sensor = sensor_get_value0(S_COR, 0.0);
		erro = valor_sensor - 34.5;
		correcao = erro * KP;
		pot_d = limitar_valor(pot_base + correcao);
		pot_e = limitar_valor(pot_base - correcao);
		printf("pot_d: %f\n", pot_d);
		printf("pot_e: %f\n", pot_e);
		tacho_set_speed_sp(MOTOR_D, vel_max * pot_d);
		tacho_set_speed_sp(MOTOR_E, vel_max * pot_e);
		tacho_run_forever(DOIS_MOTORES);
	}
}

int main(){
	if (! brick_init()) {
		printf("brick nao esta ok\n");
		return 1;
	}
	printf("brick inicializado\n");
	if (! (verificaMotores() && verificaSensores())) {
		brick_uninit();
		return 1;
	}
	printf("motores e sensores ok\n");

	seguir_linha();

	brick_uninit();
	return 0;
}
