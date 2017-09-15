define(`ALPHA', `a')dnl

define(`ALPHAR', `abcdefghijklmnopqrstuvwxyz')dnl

define(`label',`a')dnl

define(`lb',` ')dnl

define(`inc', `lb LAD $1 
  SAX  
  SXD $1')dnl

define(`dec', `lb DEC $1')dnl

define(`clr', `lb CLR $1')dnl

define(`menor', `')dnl

define(`igual', `')dnl

define(`begin', `')dnl

define(`program', `')dnl

define(`end_program', `lb END  ')dnl

define(`soma', `lb LAD $1
  ADD $2
  SAD $1')dnl

define(`sub', `lb LAD $1
  SUB $2
  SAD $1')dnl

define(`se', `lb LAD $1
  SUB $3
  ifelse($2,menor,`JGZ',$2, maior,`JLZ',$2, igual, `JZE') label
pushdef(`end_program',`popdef(`end_program')dnl'
label` DC 0
end_program')dnl
pushdef(`end_se', `pushdef(`lb',`popdef(`lb')''label`)dnl')dnl
pushdef(`ALPHAR', substr(ALPHAR,1))dnl
pushdef(`label', translit(`a',ALPHA,ALPHAR))dnl')dnl

define(`end_se', `popdef(end_se)')dnl

define(`para', `')dnl

define(`end_para', `')dnl

define(`ler', `lb INP $1')dnl

define(`escrever', `lb OUT $1')dnl

define(`int', `pushdef(`end_program',`popdef(`end_program')dnl
$1 DC $2
end_program')dnl')dnl

define(`end',`lb HLT  ')dnl
