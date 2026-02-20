#!/bin/bash
rsync -avz --delete ./my_site/ yamata-no-orochi-server:/var/www/my_site/
ssh yamata-no-orochi-server 'sudo systemctl reload nginx'

