# Aletheia Network API

## Definitions

### `<User-JSON>` (* indicates updatable field)

```json
{
  "pk": 1,
  "username": "abc123"*,
  "firstName": "first"*,
  "lastName": "last"*,
  "keyHash": "KEY"
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
204 - Successfully logged in
401 - Invalid credentials
```

---

## `/logout`

### Mark the active user session as ended.

**Request**

```http request
POST /logout HTTP/1.1
# Note: The details of this endpoint will change in the future
```

**Response**

```text
204 - Successfully ended session
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

```text
204 - Successfully updated user details
400 - Missing primary key field
404 - User with the given primary key was not found
```

### Delete a User

**Request**

```http request
DELETE /user HTTP/1.1
Content-Type: application/json

{
  "pk": 99
}
```

**Response**

```text
204 - Delete request was carried out (note: doesn't mean anything was deleted)
400 - Missing primary key field
```

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

```text
204 - Successfully updated account details
400 - Missing primary key field
404 - Account with the given primary key was not found
```

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

```text
204 - Delete request was carried out (note: doesn't mean anything was deleted)
400 - Missing primary key field
```

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

```text
204 - The key replacement request was carried out successfully
400 - Missing primary key field
404 - Account with the given primary key was not found
```
