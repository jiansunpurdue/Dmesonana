time root -b > an.log 2>&1 <<EOI
.x MCDataComparison.C+(0,0)
.q
EOI

time root -b > an.log 2>&1 <<EOI
.x MCDataComparison.C+(0,1)
.q
EOI


time root -b > an.log 2>&1 <<EOI
.x MCDataComparison.C+(1,0)
.q
EOI

