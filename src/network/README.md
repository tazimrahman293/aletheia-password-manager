# Aletheia Network API

## Definitions

### `<User-JSON>` (* indicates updatable field)

```json
{
  "pk": 1,
  "firstName": "first"*,
  "lastName": "last"*,
  "keyHash": "KEY",
  "typeID": 1*
}
```

### `<Account-JSON>` (* indicates updatable field)

```json
{
  "pk": 1,
  "label": "steam"*,
  "username": "john_doe"*,
  "keyHash": "KEY",
  "url": "steampowered.com"*,
  "created": 3457345,
  "lastAccessed": 32453576,
  "lastModified": 32345667,
  "expiry": 345678*,
  "userID": 1
}
```
---

## `/hello`

### Used for testing connection to the server.

**Request**

```http request
GET /hello HTTP/1.1
```

**Response**

```text
Hello, world!
```

---

## `/login`

### Check user credentials and, if valid, begin a new session.

**Request**

```http request
POST /login HTTP/1.1
Content-Type: application/json

{
  "pk": 1,
  "key": "PLAIN-TEXT-KEY"
}
```

**Response**

```text
200 - Successfully logged in
401 - Invalid credentials
```

---

## `/logout`

### Mark the active user session as ended.

**Request**

```http request
POST /logout HTTP/1.1
# Note: this endpoint will change in the future
```

**Response**

```text
200 - Successfully ended session
```

---

## `/user`

### Create a new User

**Request**

```http request
POST /user HTTP/1.1
Content-Type: application/json

<User-JSON>
```

**Response**

```json
{
  "pk": 1  // The pk of the newly created User
}
```

### List all Users in current database

**Request**

```http request
GET /user HTTP/1.1
```

**Response**

```json
[
  <User-JSON>,
  <User-JSON>,
  // ...
]
```

### Update an existing User

**Request**

```http request
PATCH /user HTTP/1.1
Content-Type: application/json

<User-JSON updatable fields>
```

**Response**

N/A

---

## `/account`

### Create a new Account

**Request**

```http request
POST /account HTTP/1.1
Content-Type: application/json

<Account-JSON>
```

**Response**

```json
{
  "created": 0,
  "lastAccessed": 0,
  "lastModified": 0,
  "pk": 4
}
```

### List all Accounts for a given User

**Request**

```http request
GET /account?user=99 HTTP/1.1
```

**Response**

```json
[
  <Account-JSON>,
  <Account-JSON>,
  // ...
]
```

### Update an existing Account

**Request**

```http request
PATCH /account HTTP/1.1
Content-Type: application/json

<Account-JSON updatable fields>
```

**Response**

N/A

### Delete an Account

**Request**

```http request
DELETE /account HTTP/1.1
Content-Type: application/json

{
  "pk": 1
}
```

**Response**

N/A

---

## `/account/key`

### Fetch the plain-text key for an Account

**Request**

```http request
GET /account/key?account=99 HTTP/1.1
```

**Response**

```json
{
  "pk": 99,
  "key": "PLAIN-TEXT-KEY"
}
```

### Replace the key for an Account

**Request**

```http request
PUT /account/key HTTP/1.1
Content-Type: application/json

{
  "pk": 99,
  "key": "PLAIN-TEXT-KEY"
}
```

**Response**

N/A
