------------------------------------------------------------------------------------
-- "$Id: tzmove.sql,v 1.1 2002/08/09 01:22:07 reedloden Exp $"
-- Channel service DB SQL file for PostgreSQL.

-- Script to run ONCE if you just updated with the new TimeZone feature stored in db
-- and you were previously using a version that was going thru browser cookies.
--
-- You should run this only once anyway. (psql cservice < update_tzmove_r.sql)

ALTER TABLE users ADD tz_setting VARCHAR(255) DEFAULT '';

