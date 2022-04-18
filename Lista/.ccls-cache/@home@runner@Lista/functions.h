void pause (float delay1) {
  if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.
  float inst1=0, inst2=0;
  inst1 = (float)clock()/(float)CLOCKS_PER_SEC;
  while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;
  return;
}