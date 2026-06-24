const express = require('express');
const path = require('path');
const bodyParser = require('body-parser');
const session = require('express-session');

const app = express();
const PORT = process.env.PORT || 3000;

const LOGIN = 'admin';
const PASSWORD = '1234';

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

app.use(
  session({
    secret: 'secureit_secret_key',
    resave: false,
    saveUninitialized: false
  })
);

app.use(express.static(path.join(__dirname, 'public')));

function checkAuth(req, res, next) {
  if (req.session.authenticated) {
    return next();
  }

  return res.redirect('/');
}

// ВСЕГДА открывается логин
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

app.post('/login', (req, res) => {
  const { login, password } = req.body;

  if (login === LOGIN && password === PASSWORD) {
    req.session.authenticated = true;
    return res.json({ success: true });
  }

  return res.status(401).json({
    success: false,
    message: 'Invalid login or password'
  });
});

app.get('/dashboard', checkAuth, (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'dashboard.html'));
});

app.get('/logout', (req, res) => {
  req.session.destroy(() => {
    res.redirect('/');
  });
});

app.listen(PORT, () => {
  console.log(`SecureIT running at http://localhost:${PORT}`);
});
