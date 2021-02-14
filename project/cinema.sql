-- phpMyAdmin SQL Dump
-- version 4.9.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Oct 20, 2019 at 08:17 PM
-- Server version: 10.4.8-MariaDB
-- PHP Version: 7.1.32

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cinema`
--

-- --------------------------------------------------------

--
-- Table structure for table `booking`
--

CREATE TABLE `booking` (
  `ticket_id` varchar(150) NOT NULL,
  `name` varchar(150) NOT NULL,
  `phone` varchar(150) NOT NULL,
  `email` varchar(150) NOT NULL,
  `m_id` varchar(150) NOT NULL,
  `time_id` varchar(150) NOT NULL,
  `seats` varchar(150) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `booking`
--

INSERT INTO `booking` (`ticket_id`, `name`, `phone`, `email`, `m_id`, `time_id`, `seats`) VALUES
('120', 'Harshitt', '2312312', 'err', '1', '3', '1_5_2_60_98_'),
('1234586398', 'Harshit', '1234567890', 'erosiousharsh2@gmail.com', '1', '1', '3-4-5-6-'),
('123475297', 'power', '123456789', 'power@gmail.com', '3', '1', '5-6-7-8-'),
('1253075', 'ADFG', '1234567', 'google@gmail.com', '5', '1', '1-2-3-4-');

-- --------------------------------------------------------

--
-- Table structure for table `movies`
--

CREATE TABLE `movies` (
  `id` int(10) UNSIGNED NOT NULL,
  `name` varchar(150) NOT NULL,
  `year` int(10) UNSIGNED NOT NULL,
  `type` varchar(150) NOT NULL,
  `screen_time` varchar(50) NOT NULL,
  `release_date` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `movies`
--

INSERT INTO `movies` (`id`, `name`, `year`, `type`, `screen_time`, `release_date`) VALUES
(1, 'War', 2019, 'Action/Thriller', '2h34m', '2 October 2019'),
(2, 'Joker', 2019, 'Drama/Thriller', '2h2m', '2 October 2019'),
(3, 'Avengers: Endgame', 2019, 'Fantase/Sci-Fi', '3h2m', '26 April 2019'),
(4, 'Rambo: Last Blood', 2019, 'Thriller/Action', '1h39m', '18 September 2019'),
(5, 'Ready Or Not', 2019, 'Mystery/Thriller', '1h34m', '27 July 2019'),
(6, 'Terminator: Dark Fate', 2019, 'Fantasy/Sci-Fi', '2h14m', '1 November 2019');

-- --------------------------------------------------------

--
-- Table structure for table `timings`
--

CREATE TABLE `timings` (
  `time_id` int(10) UNSIGNED NOT NULL,
  `time_day` varchar(150) NOT NULL,
  `time_noon` varchar(150) NOT NULL,
  `time_night` varchar(150) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `timings`
--

INSERT INTO `timings` (`time_id`, `time_day`, `time_noon`, `time_night`) VALUES
(1, '10:50 AM', '3:15 PM', '9:55 PM'),
(2, '11:30 AM', '5:00 PM', '11:00 PM'),
(3, '10:00 AM', '12:00 PM', '8:00 PM'),
(4, '10:45 AM', '1:20 PM', '7:15 PM'),
(5, '10:15 AM', '3:15 PM', '7:43 PM'),
(6, '10:20 AM', '12:30 PM', '9:00 PM');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `booking`
--
ALTER TABLE `booking`
  ADD PRIMARY KEY (`ticket_id`),
  ADD UNIQUE KEY `ticket_id` (`ticket_id`);

--
-- Indexes for table `movies`
--
ALTER TABLE `movies`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `timings`
--
ALTER TABLE `timings`
  ADD PRIMARY KEY (`time_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `movies`
--
ALTER TABLE `movies`
  MODIFY `id` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
