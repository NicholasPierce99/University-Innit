DROP TABLE IF EXISTS personalInfo;
CREATE TABLE personalInfo (
	ID integer primary key not null,
	name varchar(30),
	BirthDate date,
	email varchar(30)

);

INSERT INTO personalInfo VALUES(null, 'Bernie Sanders', '12/8/1776', 'feelthebern@hotmail.com');
INSERT INTO personalInfo VALUES(null, 'Donald Trump', '12/8/1700', 'theDon@gmail.com');
INSERT INTO personalInfo VALUES(null, 'Oprah Winfrey', '1/1/1111', 'oprah@theo.com');
INSERT INTO personalInfo VALUES(null, 'Mike Pence', '1/11/1111', 'pence@pence.com');


DROP TABLE IF EXISTS party;
CREATE TABLE party (
	ID integer primary key not null,
  	name VARCHAR(30)

);

INSERT INTO party VALUES (null, 'Democrat');
INSERT INTO party VALUES (null, 'Republican');
INSERT INTO party VALUES (null, 'Independent');


DROP TABLE IF EXISTS biography;
CREATE TABLE biography (
	ID integer primary key not null,
	name VARCHAR(100)
);
INSERT INTO biography VALUES(null, 'Bernie Sanders was a candidate for the Democratic Party’s 2016 presidential nomination. Sanders has served as a U.S. Senator from Vermont since 2012. He represented Vermont’s at-large congressional district from 1991 to 2007 and served as the mayor of Burlington from 1981 – 1989. Sanders is an alumnus of the University of Chicago.');
INSERT INTO biography VALUES(null, 'Donald Trump is President elect of the United States. Trump was a New York City based real estate developer, television personality and author. Trump is an alumnus of Fordham University and the Wharton School of Finance and Commerce.');
INSERT INTO biography VALUES(null, 'Oprah Winfrey is an American television host most notable for her "Oprah Show" and subsequent the "O" network, she is one of the most successful and wealthy talk show hosts in American televeision');
INSERT INTO biography VALUES(null, 'Mike Pence is the nominee for the Republican Party’s 2016 Vice Presidential nomination and has served as a Governor of Indiana since 2013. Pence served as a Member of the U.S. House of Representatives from Indiana’s from 2001 to 2013. Pence is an alumnus of Hanover College and the Indiana University School of Law.');

DROP TABLE IF EXISTS aggregateAccount;
CREATE TABLE aggregateAccount (
  	ID integer primary key not null,
  	personalInfoID int,
  	partyID int,
  	biographyID int
);

INSERT INTO aggregateAccount VALUES(null, 1, 3, 1);
INSERT INTO aggregateAccount VALUES(null, 2, 2, 2);
INSERT INTO aggregateAccount VALUES(null, 3, 1, 3);
INSERT INTO aggregateAccount VALUES(null, 4, 2, 4); 

DROP VIEW IF EXISTS accountView;
CREATE VIEW accountView AS
SELECT  
	personalInfo.name AS 'Name', 
	personalInfo.BirthDate AS 'Birth Date', 
	personalInfo.email AS 'Email',
	biography.name as 'Biography',
	party.name as 'Party'
FROM 
	personalInfo, biography, party, aggregateAccount
WHERE
	personalInfo.ID = personalInfoID
AND 
	party.ID = partyID
AND
	biography.ID = biographyID;


SELECT * FROM accountView;


DROP TABLE IF EXISTS yesNo;
CREATE TABLE yesNo (
  ID integer primary key not null,
  response VARCHAR(10)
);
INSERT INTO yesNo VALUES(null, 'Yes');
INSERT INTO yesNo VALUES(null, 'No');

DROP TABLE IF EXISTS yesNo2;
CREATE TABLE yesNo2 (
  ID integer primary key not null,
  response VARCHAR(10)
);
INSERT INTO yesNo2 VALUES(null, 'Yes');
INSERT INTO yesNo2 VALUES(null, 'No');

DROP TABLE IF EXISTS yesNo3;
CREATE TABLE yesNo3 (
  ID integer primary key not null,
  response VARCHAR(10)
);
INSERT INTO yesNo3 VALUES(null, 'Yes');
INSERT INTO yesNo3 VALUES(null, 'No');

DROP TABLE IF EXISTS socialIssues;
CREATE TABLE socialIssues (
	ID integer primary key not null,
  	issues VARCHAR(50)
);
INSERT INTO socialIssues VALUES(null, 'Should teachers be allowed to carry guns at school?');
INSERT INTO socialIssues VALUES(null, 'Should there be more restrictions on the current process of purchasing a gun?');
INSERT INTO socialIssues VALUES(null, 'Should people on the “no-fly list” be banned from purchasing guns and ammunition?');


DROP TABLE IF EXISTS immigrationIssues;
CREATE TABLE immigrationIssues (
	ID integer primary key not null,
  	issues VARCHAR(50)
);
INSERT INTO immigrationIssues VALUES(null, 'Should immigrants be deported if they commit a serious crime?');
INSERT INTO immigrationIssues VALUES(null, 'Should the U.S. build a wall along the southern border?');
INSERT INTO immigrationIssues VALUES(null, 'Should sanctuary cities receive federal funding?');

DROP TABLE IF EXISTS healthcareIssues;
CREATE TABLE healthcareIssues (
	ID integer primary key not null,
  	issues VARCHAR(50)
);
INSERT INTO healthcareIssues VALUES(null, 'Do you support the Patient Protection and Affordable Care Act (Obamacare)?');
INSERT INTO healthcareIssues VALUES(null, 'Should health insurers be allowed to deny coverage to individuals who have a pre-existing condition?');
INSERT INTO healthcareIssues VALUES(null, 'Do you support a single-payer healthcare system?');

DROP TABLE IF EXISTS issuesTotal;
CREATE TABLE issuesTotal (
	ID integer primary key not null,
	socialIssuesID int,
	immigrationIssuesID int,
	healthcareIssuesID int
);
INSERT INTO issuesTotal VALUES(null, 1, 1, 1);
INSERT INTO issuesTotal VALUES(null, 2, 2, 2);
INSERT INTO issuesTotal VALUES(null, 3, 3, 3);

DROP TABLE IF EXISTS responseLink;
CREATE table responseLink (
  ID integer primary key not null,
  personalInfoID int,
  socialIssuesID int,
  responseOneID int,
  immigrationIssuesID int,
  responseTwoID int,
  healthCareIssuesID int,
  responseThreeID int
);
INSERT INTO responseLink VALUES(null, 1, 1, 2, 1, 1, 1, 1);
INSERT INTO responseLink VALUES(null, 1, 2, 1, 2, 2, 2, 2);
INSERT INTO responseLink VALUES(null, 1, 3, 1, 3, 1, 3, 1);

INSERT INTO responseLink VALUES(null, 2, 1, 1, 1, 1, 1, 2);
INSERT INTO responseLink VALUES(null, 2, 2, 2, 2, 1, 2, 2);
INSERT INTO responseLink VALUES(null, 2, 3, 2, 3, 2, 3, 2);

INSERT INTO responseLink VALUES(null, 3, 1, 2, 1, 1, 1, 1);
INSERT INTO responseLink VALUES(null, 3, 2, 1, 2, 2, 2, 2);
INSERT INTO responseLink VALUES(null, 3, 3, 1, 3, 1, 3, 2);

INSERT INTO responseLink VALUES(null, 4, 1, 2, 1, 2, 1, 2);
INSERT INTO responseLink VALUES(null, 4, 2, 1, 2, 1, 2, 1);
INSERT INTO responseLink VALUES(null, 4, 3, 1, 3, 2, 3, 1);


DROP VIEW IF EXISTS responseView;
CREATE VIEW responseView AS
SELECT
	personalInfo.name AS 'Name',
	socialIssues.issues AS 'Social Issues',
	yesNo.response AS 'Response',
	immigrationIssues.issues AS 'Immigration Issues',
	yesNo2.response AS 'Response',
	healthcareIssues.issues AS 'Healthcare Issues',
	yesNo3.response AS 'Response'
FROM 
	personalInfo, socialIssues, immigrationIssues, yesNo, responseLink, yesNo2, healthcareIssues, yesNo3
WHERE
	personalInfo.ID = personalInfoID
AND 
	socialIssues.ID = socialIssuesID
AND
	yesNo.ID = responseOneID
AND
	immigrationIssues.ID = immigrationIssuesID
AND
	yesNo2.ID = responseTwoID
AND
	healthcareIssues.ID = healthcareIssuesID
AND 
	yesNo3.ID = responseThreeID;



DROP VIEW IF EXISTS issuesView;
CREATE VIEW issuesView AS
SELECT
  socialIssues.issues AS 'Social Issues',
  immigrationIssues.issues AS 'Immigration Issues',
  healthcareIssues.issues AS 'Healthcare Issues'
FROM 
	socialIssues, immigrationIssues, healthcareIssues, issuesTotal
WHERE
	socialIssues.ID = socialIssuesID
AND
	immigrationIssues.ID = immigrationIssuesID
AND
	healthcareIssues.ID = healthcareIssuesID;



