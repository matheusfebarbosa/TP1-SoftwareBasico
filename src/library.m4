define(`ALPHA', `a')dnl

define(`ALPHAR', `abcdefghijklmnopqrstuvwxy')dnl

define(`label',`a')dnl

define(`lb',` ')dnl

define(`begin', `')dnl

define(`program', `')dnl

define(`inc', `lb LAD $1 
  ADD z  
  SAD $1')dnl

define(`dec', `lb LAD $1 
  SUB z  
  SAD $1')dnl

define(`clr', `lb LAD y
  SAD $1')dnl

define(`ler', `lb INP $1')dnl

define(`escrever', `lb OUT $1')dnl

define(`int', `pushdef(`end_program',`popdef(`end_program')dnl
$1 DC $2
end_program')dnl')dnl

define(`end_program', `y DC 0
z DC 1
lb END  ')dnl

define(`end_se', `popdef(end_se)')dnl

define(`end',`lb HLT  ')dnl

define(`soma', `lb LAD $2
  ADD $3
  SAD $1')dnl

define(`sub', `lb LAD $2
  SUB $3
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

define(`para', `  LCD label
pushdef(`end_program',`popdef(`end_program')dnl'
label` DC eval($3-$2+1)
end_program')dnl
pushdef(`ALPHAR', substr(ALPHAR,1))dnl
pushdef(`label', translit(`a',ALPHA,ALPHAR))dnl
  LAD label
  SAD $1
pushdef(`end_program',`popdef(`end_program')dnl'
label` DC $2
end_program')dnl
pushdef(`ALPHAR', substr(ALPHAR,1))dnl
pushdef(`label', translit(`a',ALPHA,ALPHAR))dnl  
pushdef(`end_para', `inc($1)
  JCC 'label`')dnl
pushdef(`lb',`popdef(`lb')'label)dnl
pushdef(`ALPHAR', substr(ALPHAR,1))`'pushdef(`label', translit(`a',ALPHA,ALPHAR))dnl')dnl

define(`end_para', `popdef(end_para)')dnl