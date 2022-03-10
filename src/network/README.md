#Aletheia Network API

---

`/hello`

**Description**

Used for testing connection to the server.

**Methods**

GET

**Request Params**

N/A

**Response**

"Hello, world!" (plain/text)

---

`/login`

**Description**

Checks the validity of a master key given for a particular user.

**Methods**

POST

**Request Body**

```json
{
  "pk": 1,
  // Key is sent in plain text for now
  "pass": "example"
}
```

**Response**

```json
{
  "pk": 1,
  "firstName": "first",
  "lastName": "last",
  "typeID": 1
}
```

---

`/logout`

**Description**

Marks the active user session as ended.

**Methods**

GET (may change to POST in the future)

**Request Params**

N/A

**Response**

N/A

---

`/new-user`

**Description**

Requests the creation of a new user profile and master key.

**Methods**

POST

**Request Body**

```json
{
  // PK doesn't matter here but it must be sent
  "pk": -1,
  "firstName": "first",
  "lastName": "last",
  // Send the key as plain text for now
  "keyHash": "PLAIN-TEXT-KEY",
  // Normal = 1, Admin = 2
  "typeID": 1
}
```

**Response**

```json
{
  "pk": 1,
  "firstName": "first",
  "lastName": "last",
  "typeID": 1
}
```

---

`/edit-user`

**Description**

Updates all the fields of a given user (except PK)

**Methods**

POST

**Request Body**

```json
{
  "pk": 1,
  "firstName": "first",
  "lastName": "last",
  // Key doesn't matter here but it must be included
  "keyHash": "",
  "typeID": 1
}
```

**Response**

```json
{
  "pk": 1,
  "firstName": "first",
  "lastName": "last",
  "typeID": 1
}
```

---

`/user-accounts`

**Description**

Gets all accounts for a given user.

**Methods**

GET

**Request Params**

```http request
GET /user-accounts?pk=1
```

**Response**

```json
[
  {
    "created": 0,
    "expiry": 0,
    "label": "my-account",
    "lastAccessed": 0,
    "lastModified": 0,
    "pk": 1,
    "url": "example.com",
    "userID": 1,
    "username": "username"
  },
  {
    "created": 0,
    "expiry": 0,
    "label": "other-account",
    "lastAccessed": 0,
    "lastModified": 0,
    "pk": 2,
    "url": "test.com",
    "userID": 5,
    "username": "john.doe"
  },
  // ...
]
```

---

`/new-account`

**Description**

Requests the creation of a new account under a given user.

**Methods**

POST

**Request Body**

```json
{
  "created": 0,
  "expiry": 0,
  "keyHash": "PLAIN-TEXT-KEY",
  "label": "some-account",
  "lastAccessed": 0,
  "lastModified": 0,
  // pk doesn't matter here but must be included
  "pk": -1,
  "url": "example.com",
  "userID": 9,
  "username": "jane_92@gmail.com"
}
```

**Response**

```json
{
  "created": 0,
  "expiry": 0,
  "label": "some-account",
  "lastAccessed": 0,
  "lastModified": 0,
  "pk": 4,
  "url": "example.com",
  "userID": 9,
  "username": "jane_92@gmail.com"
}
```

---

`/edit-account`

**Description**

Updates all the fields of an existing account.

**Methods**

POST

**Request Body**

```json
{
  "created": 0,
  "expiry": 0,
  "keyHash": "",
  "label": "some-account",
  "lastAccessed": 0,
  "lastModified": 0,
  "pk": 2,
  "url": "example.com",
  "userID": 9,
  "username": "jane_92@gmail.com"
}
```

**Response**

```json
{
  "created": 0,
  "expiry": 0,
  "label": "some-account",
  "lastAccessed": 0,
  "lastModified": 0,
  "pk": 4,
  "url": "example.com",
  "userID": 9,
  "username": "jane_92@gmail.com"
}
```

---

`/remove-account`

**Description**

Deletes an existing account.

**Methods**

POST

**Request Body**

```json
{
  "pk": 1
}
```

**Response**

N/A

---

`/account-key`

**Description**

Fetches the plain-text key for an account.

**Methods**

POST (change to GET)

**Request Params**

```http request
GET /account-key?pk=1
```

**Response**

```json
{
  "pk": 1,
  "key": "PLAIN-TEXT-KEY"
}
```

---

`/edit-key`

**Description**

Replaces the plain-text key for an account.

**Methods**

POST

**Request Body**

```json
{
  "pk": 1,
  "key": "PLAIN-TEXT-KEY"
}
```

**Response**

N/A
