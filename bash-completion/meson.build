if get_option('bash-completions')
bash_completions = [
  'openrc',
  'rc-service',
  'rc-status',
  'rc-update',
  ]

install_data(bash_completions,
  install_dir : get_option('datadir') / 'bash-completion/completions')
endif
