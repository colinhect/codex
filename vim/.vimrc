set expandtab
set tabstop=4
syntax on

" Add codex source and assembly file types
au BufRead,BufNewFile *.cxs set filetype=codex
au! Syntax codex source ~/.vim/syntax/codex.vim
  
function! Codex()
	exec '%s/<=/≤/g'
	exec '%s/>=/≥/g'
	exec '%s/==/=/g'
	exec '%s/!=/≠/g'
	exec '%s/->/➔/g'
	exec '%s/*/∙/g'
	exec '%s/!/¬/g'
	exec '%s/&&/∧/g'
	exec '%s/||/∨/g'
endfunction

