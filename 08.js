// SQL injection

const http = require('http');
const mysql = require('mysql');

// SQL connection
const db = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'password',
    database: 'mydatabase'
});

// Vulnerable endpoint
const valnarableEndpoint = (username, password, callback) => {
    const query = 'SELECT * FROM users WHERE username = ? AND password = ?';
    db.query(query, [username, password], (err, results) => {
        if (err) {
            callback(err, null);
            return;
        }
        callback(null, results);
    });
};

// server login
http.createServer((req, res) => {
    if (req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            const { username, password } = JSON.parse(body);
            valnarableEndpoint(username, password, (err, results) => {
                if (err) {
                    res.writeHead(500, { 'Content-Type': 'text/plain' });
                    res.end('Internal Server Error');
                    return;
                }
                if (results.length > 0) {
                    res.writeHead(200, { 'Content-Type': 'text/plain' });
                    res.end('Login successful');
                } else {
                    res.writeHead(401, { 'Content-Type': 'text/plain' });
                    res.end('Invalid username or password');
                }
            });
        });
    }
}).listen(3000);

console.log('Server running at http://localhost:3000/');
